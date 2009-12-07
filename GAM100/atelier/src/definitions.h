#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Magic numbers.
#define MAX_INPUT_LENGTH 80

// General types.

enum boolean
{
	FALSE,
	TRUE
};

typedef enum boolean BOOL;

// Interactions.

enum COMMAND_LIST
{
	INVALID,
	// Menu and metagame stuff.
	SAVE,
	QUIT,
	// In-game stuff.
	MOVE,
	CREATE,
	REMOVE,
	ATTACH
};

struct COMMAND
{
	enum COMMAND_LIST order;
	int value;
};

#endif

