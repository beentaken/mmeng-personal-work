#include "network.hpp"

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#elif defined(_WIN32)
#include <winsock2.h>
#endif

#include <cstring>
#include <stdexcept>
#include <iostream>

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
}

NetworkStack::NetworkStack()
    :myCurrentConnections(), listener()
{
    FD_ZERO(&myConnections);
}

NetworkStack::~NetworkStack()
{
    // On windows: WSACleanUp
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
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
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
    std::cout << "Thinking..." << std::endl;
    fd_set read_fds;  // temp file descriptor list for select()
    FD_ZERO(&read_fds);

    char buf[256];    // buffer for client data
    int nbytes;

    // main loop
    std::cout << "Entering main loop." << std::endl;
    read_fds = myConnections; // copy it
    std::cout << "Running select on read set." << std::endl;
    if (select(myCurrentConnections+1, &read_fds, NULL, NULL, NULL) == -1)
    {
        perror("select");
        throw(std::runtime_error("Select error."));
    }

    std::cout << "Checking connections." << std::endl;

    // run through the existing connections looking for data to read
    for(int i = 0; i <= myCurrentConnections; ++i)
    {
        if (FD_ISSET(i, &read_fds))
        { // we got one!!
            if (i == listener)
            {
                // Listener has data, new connection.
                sockaddr_storage remoteaddr; // New client address.
                // handle new connections
                socklen_t addrlen = sizeof(remoteaddr);
                // Set up new file descriptor.
				int newfd = accept(listener,
				reinterpret_cast<sockaddr *>(&remoteaddr),
					&addrlen);

				if (newfd == -1)
                {
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
                }
            }
            else
            {
                // handle data from a client
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
                    close(i); // bye!
                    FD_CLR(i, &myConnections); // remove from myConnections set
                }
                else
                {
                    // we got some data from a client
                    std::string temp;
                    temp.assign(buf, nbytes);
                    std::cout << "Recieved: " << temp << std::endl;
                    for(int j = 0; j <= myCurrentConnections; j++)
                    {
                        // send to everyone!
                        if (FD_ISSET(j, &myConnections))
                        {
                            // except the listener and ourselves
                            if (j != listener && j != i)
                            {
                                if (send(j, buf, nbytes, 0) == -1)
                                {
                                    perror("send");
                                }
                            }
                        }
                    }
                }
            } // END handle data from client
        } // END got new incoming connection
    } // END looping through file descriptors
}

