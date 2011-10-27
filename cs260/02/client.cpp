#include <iostream>
#include <string>
#include <istream>
#include "network.hpp"

#include <boost/thread.hpp>

struct NetworkThinker
{
    NetworkStack& ns;

    NetworkThinker(NetworkStack& new_ns)
        :ns(new_ns)
    {
    }

    void operator()()
    {
        while (true)
        {
            ns.think();
        }
    }
};

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
    void operator()(int /* connection */, const std::string& message)
    {
        std::cout << message << std::endl;
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

        // Actually, just make us quit.
        exit(0);
    }
};

int ConnectionGrabber::connection = -1;

int main()
{
    std::string address, port;

    std::cout << "Please enter the IP address of the server: ";
    std::getline(std::cin, address);
    std::cout << "Please enter the port of the server: ";
    std::getline(std::cin, port);
    NetworkStack ns;

    bool quit = false;
    ns.registerConnectListener(ConnectionGrabber());
    ns.registerReceiveListener(MessagePrinter());
    ns.registerDisconnectListener(QuitFlagger(quit));
    ns.connect(address, port);
    
    boost::thread network_thread((NetworkThinker(ns)));

    while (!quit)
    {
        //ns.think();
        std::string buffer;
        std::cout << ">> ";
        std::getline(std::cin, buffer);

        ns.sendString(ConnectionGrabber::connection, buffer);
    }
    
    return(0);
}

