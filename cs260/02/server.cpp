#include <iostream>

#include "network.hpp"

int main()
{
    std::cout << "Starting..." << std::endl;
    NetworkStack netcode;

    netcode.listen("9034");

    // think of this as a game loop.
    while(true)
    {
        netcode.think();
    }

    return(0);
}

