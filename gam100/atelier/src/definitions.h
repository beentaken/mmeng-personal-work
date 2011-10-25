#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Magic numbers.
#define MAX_INPUT_LENGTH 80

// Interactions.

enum COMMAND_LIST
{
	INVALID,
	// Menu and metagame stuff.
	SAVE,
	NEW_GAME,
	RETURN_TO_MENU,
	CREDITS,
	HELP,
	QUIT,
	// In-game stuff.
	MOVE,
	CREATE,
	REMOVE,
	SWITCH_LINES
};

struct COMMAND
{
	enum COMMAND_LIST order;
	int value;
};

#endif

