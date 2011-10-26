#include <iostream>
#include <string>

#include "network.hpp"

class MessageEchoer
{
    NetworkStack& myStack;
    public:
        MessageEchoer(NetworkStack& ns)
            :myStack(ns)
        {
        }

        void operator()(int connection, const std::string& message)
        {
            std::cout << "Echo message from " << connection << ": " << message << std::endl;

            if (message == "/quit")
            {
                std::cout << "Disconnecting connection " << connection << std::endl;
                myStack.disconnect(connection);
                return;
            }

            // Echo it back.
            myStack.sendString(connection, message);
        }
};

void PrintMessage(int connection, const std::string& message)
{
    std::cout << "Receive message from " << connection << ": " << message << std::endl;
}

int main()
{
    std::cout << "Starting..." << std::endl;
    NetworkStack netcode;

    //netcode.registerReceiveListener(&PrintMessage);
    netcode.registerReceiveListener(MessageEchoer(netcode));

    netcode.listen("9034");

    // think of this as a game loop.
    while(true)
    {
        netcode.think();
    }

    return(0);
}

