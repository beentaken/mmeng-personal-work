#include <iostream>
#include <string>
#include <fstream>

#include "network.hpp"
#include "chess.hpp"

int main()
{
    std::cout << "Starting..." << std::endl;
    std::string address, port;
    std::fstream config_file("config.txt");
    std::getline(config_file, address);
    std::getline(config_file, port);
    NetworkStack netcode;

    Chess::Server chess_server(netcode);
    netcode.registerAcceptListener(Chess::ServerAcceptAdapter(chess_server));
    netcode.registerReceiveListener(Chess::ServerReceiveAdapter(chess_server));

    netcode.listen(port);

    // think of this as a game loop.
    while(true)
    {
        netcode.think();
    }

    return(0);
}

