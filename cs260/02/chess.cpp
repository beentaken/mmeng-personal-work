#include "chess.hpp"

#include <algorithm> // for_each
#include <stdexcept> // runtime_error
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

namespace Chess
{
    /*************************************************************************
     * Player class
     */
    Player::Player()
        :myConnection(-1), myName(), myInGameFlag(-1)
    {
    }

    Player::Player(int connection, const std::string new_name)
        :myConnection(connection), myName(new_name), myInGameFlag(-1)
    {
    }

    Player& Player::setName(const std::string& new_name)
    {
        myName = new_name;

        return(*this);
    }

    const std::string& Player::getName() const
    {
        return(myName);
    }

    Player& Player::setConnection(int connection)
    {
        myConnection = connection;

        return(*this);
    }

    int Player::getConnection() const
    {
        return(myConnection);
    }

    Player& Player::setInGame(int game_index)
    {
        myInGameFlag = game_index;

        return(*this);
    }

    int Player::inGame() const
    {
        return(myInGameFlag);
    }

    bool Player::operator==(const Player& rhs) const
    {
        return(myConnection == rhs.getConnection());
    }

    /*************************************************************************
     * Game class
     */
    Game::Game(Player& new_p1, Player& new_p2, Server& server)
        :p1(new_p1), p2(new_p2), myServer(server), myP1Turn(true),
        myBoard(), myActiveFlag(false)
    {
    }

    Game::~Game()
    {
        myActiveFlag = false;
    }

    void Game::move(const Player& actor, const std::string& move)
    {
        if ((actor == p1 && !myP1Turn) || (actor == p2 && myP1Turn))
        {
            myServer.messagePlayer(actor, "Not your turn!");
        }
        else
        {
            // TODO: Parse and make the move!
            // For now, just nothing.
            myServer.messagePlayer(actor, move);
        }
    }

    std::string Game::getBoard() const
    {
        // TODO: Return the actual board. For now, just a dummy.
        return("This is meant to be a board.");
    }

    Game& Game::setActive()
    {
        myActiveFlag = true;
        return(*this);
    }

    Game& Game::setInactive()
    {
        myActiveFlag = false;
        return(*this);
    }

    bool Game::getActive() const
    {
        return(myActiveFlag);
    }

    /*************************************************************************
     * Server class.
     */

    Server::Server(NetworkStack& ns)
        :myNetwork(ns), myPlayerList(), myGameList()
    {
    }

    const Player& Server::getPlayer(const std::string& by_name) const
    {
        return(myPlayerList.at(by_name));
    }

    const Player& Server::getPlayer(int by_connection) const
    {
        for (auto it = myPlayerList.begin(); it != myPlayerList.end(); ++it)
        {
            if (it->second.getConnection() == by_connection)
                return(it->second);
        }

        // Invalid, wut
        throw(std::runtime_error("Invalid connection passed into getPlayer."));
    }

    void Server::messagePlayer(const Player& receiver, const std::string& message)
    {
        myNetwork.sendString(receiver.getConnection(), message);
    }

    void Server::processInput(int connection, const std::string& input)
    {
        std::cout << "Connection " << connection << ": " << input << std::endl;

        try
        {
            Player temp = getPlayer(connection);
            
            if (input == "/quit")
            {
                unregisterPlayer(temp);

                std::cout << "Removed player on connection " << connection << std::endl;
            }
            else if (input == "/show")
            {
                if (temp.inGame() < 0)
                {
                    messagePlayer(temp, "Invalid command, not in a game!");
                }
                else
                {
                    messagePlayer(temp, (myGameList[temp.inGame()].getBoard()));
                }
            }
            else if (input == "/list")
            {
                messagePlayer(temp, getPlayerList());
            }
            else if (input == "/forfeit")
            {
                messagePlayer(temp, "Forfeit game message.");
            }
            else if (input.find("/play") == 0)
            {
                messagePlayer(temp, "Play game message.");
                std::stringstream ss(input);
                std::istream_iterator<std::string> it(ss);
                
                std::vector<std::string> tokens(it, std::istream_iterator<std::string>());

                Player potential_p2;

                try
                {
                    potential_p2 = getPlayer(tokens[1]);
                }
                catch(std::runtime_error&)
                {
                    messagePlayer(temp, "No such player exists.");
                }

                if (potential_p2 == temp)
                {
                    messagePlayer(temp, "No single player!");
                }
                else if (potential_p2.inGame() != -1)
                {
                    messagePlayer(temp, "That party is already in a game.");
                }
                else
                {
                    messagePlayer(temp, "Creating game.");
                    messagePlayer(potential_p2, temp.getName() + " started a game with you!");
                }
            }
            else if (input == "/help")
            {
                messagePlayer(temp, "Valid commands: /help /list /show /quit /play /forfeit");
            }
            else
            {
#if 1
                std::cout << "Broadcasting to lobby." << std::endl;
                for (auto it = myPlayerList.begin(); it != myPlayerList.end(); ++it)
                {
                    if (it->second.inGame() < 0 && !(it->second == temp))
                        messagePlayer(it->second, temp.getName() + ": " + input);
                }
#else
                std::cout << "Echoing message." << std::endl;
                messagePlayer(temp, temp.getName() + ": " + input);
#endif
            }
        }
        catch(std::runtime_error&) // Probably because the player didn't exist!
        {
            // New player, this message should be the name.
            //myPlayerList.emplace(input, connection, input);
            myPlayerList[input] = Player(connection, input);
            std::cout << "Player created with name " << input << '.' << std::endl;
            messagePlayer(myPlayerList[input], "Username registered.");
        }
    }

    void Server::registerPlayer(int connection)
    {
        std::cout << "Got a new connection, setting up player." << std::endl;
        myNetwork.sendString(connection, "Please enter a username: ");
    }

    void Server::unregisterPlayer(Player& player)
    {
        myNetwork.disconnect(player.getConnection());
        myPlayerList.erase(player.getName());
    }

    std::string Server::getPlayerList() const
    {
        std::string to_return;
		const std::unordered_map<std::string, Player>& temp = myPlayerList;

        std::for_each(myPlayerList.begin(), myPlayerList.end(),
                [&to_return, &temp](std::pair<std::string, Player> x){ to_return += x.second.getName();
                to_return+= " (";
                to_return+= (x.second.inGame() != -1) ? "In Game" : "Available";
                to_return+= ")\n"; });

        return(to_return);
    }
}

