Assignment 02 (Chess Server)
CS260 (Tucker)
Student: Marcus Meng (marcus.meng@digipen.edu)

This is the second assignment for CS260.

The system comes in two parts, the client, and the server.

The server will read config.txt upon startup, and listen on the specified
port. The address in the config file is completely ignored.

The client will prompt the user for an address and a port interactively upon
startup.

Once connected, the client will be prompted for a name. Upon successful name
registration, the client can then use the following commands:

/quit: Exits the program immediately.
/play <name>: Attempts to start a game with the user of the given name.
/list: Lists all users on the server and their status.
/show: Shows the game board. Only functions when in a game.
/forfeit: Forfeits a game and returns the player to the lobby.
/help: Displays an abbreviated list of commands.

When in the lobby, any input that is not recognized as a command is assumed to
be chat text, and is broadcasted to all other players present in the lobby.

