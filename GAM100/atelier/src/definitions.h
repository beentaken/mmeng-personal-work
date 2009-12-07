#ifndef DEFINITIONS_H
#define DEFINITIONS_H

enum boolean
{
	FALSE,
	TRUE
};

typedef enum boolean BOOL;

enum COMMAND_LIST
{
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

