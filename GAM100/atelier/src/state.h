#ifndef STATE_H
#define STATE_H

#include "definitions.h"
#include "units.h"

#define MAX_LINES 5

enum STATE
{
	MENU,
	GAME
};

struct GAMESTATE
{
	enum STATE current_state;
	int current_line;

	unit *lines[MAX_LINES];
	unit *pool;
};

void initialize_game_state(struct GAMESTATE *state);
void destroy_game_state(struct GAMESTATE *state);

#endif

