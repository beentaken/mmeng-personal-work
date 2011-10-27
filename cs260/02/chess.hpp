#pragma once
#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <unordered_map>
#include <vector>
#include <array>

#include "network.hpp"

namespace Chess
{
    // Forward decl
    class Server;

    class Player
    {
        public:
            Player();
            Player(int connection, const std::string new_name);

            Player& setName(const std::string& new_name);
            const std::string& getName() const;

            Player& setConnection(int connection);
            int getConnection() const;

            int inGame() const;
            Player& setInGame(int game_index);

            bool operator==(const Player& rhs) const;
        private:
            int myConnection;
            std::string myName;

            // This flag is set to -1 if the player is not in a game, and the
            // game's index otherwise.
            mutable int myInGameFlag;
    };

    class Game
    {
        public:
            typedef std::array<std::array<char, 8>, 8> Board;

            Game(Player& new_p1, Player& new_p2, Server& server);
            ~Game();

            // Moves a piece, or sends the player a message if it is not his
            // turn.
            void move(const Player& actor, const std::string& move);

            // Returns a big string representation of the chessboard.
            // Can be printed immediately.
            std::string getBoard() const;

            Game& setActive();
            Game& setInactive();

            bool getActive() const;

        private:
            Player& p1;
            Player& p2;
            Server& myServer; // The server this game is on.
            bool myP1Turn; // Is it player 1's turn?
            Board myBoard;
            bool myActiveFlag;
    };

    // Handles the lobby, player registry, and game registry.
    class Server
    {
        public:
            Server(NetworkStack& ns);
            std::string getPlayerList() const;

            const Player& getPlayer(const std::string& by_name) const;
            const Player& getPlayer(int by_connection) const;

            void registerPlayer(int connection);
            void unregisterPlayer(Player& player);
            // Sends a message to a given player handle.
            void messagePlayer(const Player& receiver, const std::string& message);

            // Recieves a message over the network and dispatches it to the
            // appropriate functions.
            void processInput(int connection, const std::string& input);
        private:
            NetworkStack& myNetwork;
            std::unordered_map<std::string, Player> myPlayerList;
            std::vector<Game> myGameList;
            
            // New game created and registered between two valid players.
            void myRegisterGame(const Player& p1, const Player& p2);
            void myUnregisterGame(Game& game);
    };

    // Useful wrappers
    struct ServerReceiveAdapter
    {
        Server& myServer;

        ServerReceiveAdapter(Server& ns)
            :myServer(ns)
        {
        }

        void operator()(int connection, const std::string& message)
        {
            myServer.processInput(connection, message);
        }
    };

    struct ServerAcceptAdapter
    {
        Server& myServer;

        ServerAcceptAdapter(Server& ns)
            :myServer(ns)
        {
        }

        void operator()(int connection)
        {
            myServer.registerPlayer(connection);
        }
    };
}
#endif // CHESS_H

