#include "network.hpp"

#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#elif defined(_WIN32)
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define close(x) (closesocket(x))
#endif

#include <cstring> // memset
#include <stdexcept> // runtime_error
#include <iostream>
#include <algorithm> // for_each

namespace
{
    // get sockaddr, IPv4 or IPv6:
    void *get_in_addr(struct sockaddr *sa)
    {
	    if (sa->sa_family == AF_INET)
        {
		    return &(((struct sockaddr_in*)sa)->sin_addr);
	    }

	    return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }

#if defined(_WIN32) && (_WIN32_WINNT < 0x600)
	// FUUUUUUU- inet_ntop is only available on Vista or higher.
	const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
	{
		int rv = WSAAddressToString(*src, af, NULL, dst, (LPDWORD)size);

		if (rv == SOCKET_ERROR)
		{
			throw(std::runtime_error("Could not convert address to string."));
		}
	}
#endif
}

NetworkStack::NetworkStack()
    :myCurrentConnections(), listener(-1), myAcceptListeners(),
    myConnectListeners(), myReceiveListeners(), myDisconnectListeners()
{
#if defined(_WIN32)
	WSADATA wsaData;
	SecureZeroMemory(&wsaData, sizeof(wsaData));
	int ret = WSAStartup(MAKEWORD(2,2), &wsaData);

	if(ret != 0)
	{
		throw(std::runtime_error("Error initializing Winsock!"));
	}
#endif
    FD_ZERO(&myConnections);
}

NetworkStack::~NetworkStack()
{
    // Which way is better?
#if 0
    while (FD_ISSET(myCurrentConnections, &myConnections))
    {
        close(myCurrentConnections);
    }
#else
    for (int i = 0; i < myCurrentConnections; ++i)
    {
        if (FD_ISSET(i, &myConnections))
            close(i);
    }
#endif

#if defined(_WIN32)
	WSACleanup();
#endif // _WIN32
}

void NetworkStack::listen(const std::string& port)
{
    std::cout << "Told to listen in port " << port << std::endl;
    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int rv; // Return value

	addrinfo hints, *ai, *p;

	// get us a socket and bind it
    std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // We don't care if it's v4 or v6
	hints.ai_socktype = SOCK_STREAM; // TCP (DATAGRAM is UDP)
	hints.ai_flags = AI_PASSIVE; // Fill in useful stuff for me.
	if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &ai)) != 0)
    {
        throw(std::runtime_error(gai_strerror(rv)));
	}
	
	for(p = ai; p != NULL; p = p->ai_next)
    {
    	listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0)
        { 
			continue;
		}
		
		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
			close(listener);
			continue;
		}

		break;
	}

	// if we got here, it means we didn't get bound
	if (p == NULL)
    {
        throw(std::runtime_error("Failed to bind socket."));
	}

	freeaddrinfo(ai); // all done with this

    // listen
    if (::listen(listener, 10) == -1)
    {
        perror("listen");
        throw(std::runtime_error("Listening error."));
    }

    // add the listener to the myConnections set
    FD_SET(listener, &myConnections);

    // keep track of the biggest file descriptor
    myCurrentConnections = listener; // so far, it's this one
}

void NetworkStack::think()
{
    fd_set read_fds;  // temp file descriptor list for select()
    FD_ZERO(&read_fds);

    char buf[256];    // buffer for client data
    int nbytes;

    // main loop
    read_fds = myConnections; // copy it
    // Last argument to select is timeout.
    // Setting the time values to 0 means poll instantly,
    // setting it to NULL basically blocks until at least one
    // descriptor frees up.
    if (select(myCurrentConnections+1, &read_fds, NULL, NULL, NULL) == -1)
    {
        perror("select");
        throw(std::runtime_error("Select error."));
    }

    // run through the existing connections looking for data to read
    for(int i = 0; i <= myCurrentConnections; ++i)
    {
        if (FD_ISSET(i, &read_fds))
        { // we got one!!
            if (i == listener)
            {
                int newfd;
                // NOTE: This is commented out because we're not using
                // nonblocking modes. This would be useful otherwise.
                //do // Do until no more new connections.
                //{
                    // Listener has data, new connection.
                    sockaddr_storage remoteaddr; // New client address.
                    // handle new connections
                    socklen_t addrlen = sizeof(remoteaddr);
                    // Set up new file descriptor.
				    newfd = accept(listener,
				        reinterpret_cast<sockaddr *>(&remoteaddr),
					    &addrlen);

				    if (newfd == -1)
                    {
                        //if (errno != EWOULDBLOCK)
                            perror("accept");
                        // Don't throw, it's just a single invalid handle.
                    }
                    else
                    {
                        FD_SET(newfd, &myConnections); // add to myConnections set
                        if (newfd > myCurrentConnections)
                        {    // keep track of the max
                            myCurrentConnections = newfd;
                        }
                        
	                    char remoteIP[INET6_ADDRSTRLEN];
                        std::cout << "New connection from "
                            << inet_ntop(remoteaddr.ss_family,
                                get_in_addr(reinterpret_cast<sockaddr*>(&remoteaddr)),
                                remoteIP, INET6_ADDRSTRLEN) << " on socket "
                            << newfd << std::endl;
                        
                        // Run all my accept listeners!
                        std::for_each(myAcceptListeners.begin(), myAcceptListeners.end(),
                                [&newfd](AcceptListenerFun x){ x(newfd); });
                    }
                //} while(newfd != -1);
            }
            else
            {
                // handle dhttp://hardware.slashdot.org/story/11/10/25/1923233/robot-walks-like-a-human-requires-no-powerata from a client
                if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
                {
                    // got error or connection closed by client
                    if (nbytes == 0)
                    {
                        // connection closed
                        std::cout << "Socket " << i << " hung up." << std::endl;
                    }
                    else
                    {
                        perror("recv");
                    }
                    myDisconnectSocket(i);
                    // Run appropriate disconnect events.
                    std::for_each(myDisconnectListeners.begin(),
                        myDisconnectListeners.end(),
                        [&i](DisconnectListenerFun x){ x(i); });
                }
                else
                {
                    // we got some data from a client
                    std::string temp;
                    temp.assign(buf, nbytes);

                    // Do stuff to the data!
                    std::for_each(myReceiveListeners.begin(), myReceiveListeners.end(),
                            [&i, &temp](ReceiveListenerFun x){ x(i, temp); });
                }
            } // END handle data from client
        } // END got new incoming connection
    } // END looping through file descriptors
}

void NetworkStack::myDisconnectSocket(int socket)
{
    close(socket);
    FD_CLR(socket, &myConnections);

    if (socket == myCurrentConnections)
    {
        while(FD_ISSET(myCurrentConnections, &myConnections) == false)
            --myCurrentConnections;
    }
    /*
    if (shutdown(socket, 2) == -1) // 2 = no further sends or recieves. Redundant after close.
    {
        perror("shutdown");
        throw(std::runtime_error("Error shutting down socket."));
    } */
}

void NetworkStack::disconnect(int connection)
{
    myDisconnectSocket(connection);
}

void NetworkStack::registerAcceptListener(AcceptListenerFun fun)
{
    myAcceptListeners.push_back(fun);
}

void NetworkStack::registerConnectListener(ConnectListenerFun fun)
{
    myConnectListeners.push_back(fun);
}

void NetworkStack::registerReceiveListener(ReceiveListenerFun fun)
{
    myReceiveListeners.push_back(fun);
}

void NetworkStack::registerDisconnectListener(DisconnectListenerFun fun)
{
    myDisconnectListeners.push_back(fun);
}

void NetworkStack::sendString(int connection, const std::string& message)
{
    if (FD_ISSET(connection, &myConnections) == false)
    {
        // Not in our connection list, uh oh.
        throw(std::runtime_error("Invalid connection."));
    }
    // Technically, send doesn't have to send everything in one
    // call. Which really sucks. But we'll pretend it's all fine.
    int rv = send(connection, message.c_str(), message.size(), 0);

    if (rv == -1)
    {
        throw(std::runtime_error("Failed to send message!"));
    }
}

void NetworkStack::connect(const std::string& address, const std::string& port)
{
    int sockfd;  
	addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        throw(std::runtime_error("Could not retrieve address information."));
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next)
    {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1)
        {
			perror("client: socket");
			continue;
		}

		if (::connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL)
    {
        throw(std::runtime_error("Could not connect."));
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    std::cout << "client: connecting to " <<  s << std::endl;

	freeaddrinfo(servinfo); // all done with this structure

    FD_SET(sockfd, &myConnections);

    if (sockfd > myCurrentConnections)
    {
        myCurrentConnections = sockfd;
    }

    std::for_each(myConnectListeners.begin(), myConnectListeners.end(),
            [&sockfd](ConnectListenerFun x){ x(sockfd); });
}

