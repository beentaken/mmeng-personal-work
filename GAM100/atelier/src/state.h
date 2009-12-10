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

/* Sets up the variables and things needed to get the game state up and
 * running.
 *
 * Preconditions: state is a pointer to an existing but uninitialized gamesate.
 * Postconditions: All member variables in state are initialized to sane
 * 		default values.
 */
void initialize_game_state(struct GAMESTATE *state);

/* Destroys any dynamically allocated memory in the gamestate.
 *
 * Preconditions: state points to an initialized gamestate.
 * Postconditions: All pointers holding dynamically allocated memory have been
 * 		released.
 */
void destroy_game_state(struct GAMESTATE *state);

#endif

