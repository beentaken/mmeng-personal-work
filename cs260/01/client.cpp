#include <iostream>
#include <string>
#include "network.hpp"

struct ConnectionGrabber
{
    static int connection;

    void operator()(int socket)
    {
        connection = socket;
        std::cout << "Grabbed connection " << connection << std::endl;
    }
};

struct MessagePrinter
{
    void operator()(int connection, const std::string& message)
    {
        std::cout << "Connection " << connection << ": " << message << std::endl;
    }
};

struct QuitFlagger
{
    bool& myFlag;
    QuitFlagger(bool &flag)
        :myFlag(flag)
    {
    }

    void operator()(int)
    {
        myFlag = true;
    }
};

int ConnectionGrabber::connection = -1;

int main()
{
    NetworkStack ns;

    bool quit = false;
    ns.registerConnectListener(ConnectionGrabber());
    ns.registerReceiveListener(MessagePrinter());
    ns.registerDisconnectListener(QuitFlagger(quit));
    ns.connect("localhost", "9034");

    while (!quit)
    {
        std::string buffer;
        std::cout << "Enter something: ";
        std::getline(std::cin, buffer);

        ns.sendString(ConnectionGrabber::connection, buffer);
        ns.think();
    }
    
    return(0);
}

