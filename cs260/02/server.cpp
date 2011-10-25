#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream> // cerr
#include <cstring> // memset
#include <stdexcept>

int main()
{
    const char* listen_port = "3490";
    int status;
    addrinfo hints;
    addrinfo* servinfo; // Store getaddrinfo results here.

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    // Don't care IPv4 or 6. AF_INET or AF_INET6 otherwise.
    hints.ai_socktype = SOCK_STREAM; // TCP (datagram is UDP)
    hints.ai_flags = AI_PASSIVE;    // Automatic IP fill.

    // Test port 3490
    if ((status = getaddrinfo(NULL, listen_port, &hints, &servinfo)) != 0)
    {
        throw(std::runtime_error(gai_strerror(status)));
    }

    // servinfo is set
    // TODO: Things
    freeaddrinfo(servinfo); // Done using it, free stuff.

    return(0);
}

