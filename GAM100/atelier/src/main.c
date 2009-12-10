/* This file should not contain more than what is needed to initialize
 * and set up a basic game loop.
 */

#include <stdio.h>

#include "game.h"
#include "state.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		puts(argv[1]);
	}

	struct GAMESTATE current_gamestate;

	initialize_game_state(&current_gamestate);
	// Hardcoding an initial setup. This will change once an actual level
	// system is implemented.

	while(game_loop(&current_gamestate));

	// Do some cleanup before we leave. Can't have the OS steal all the
	// fun, after all, right?
//	destroy_all_units(head);

	return 0;
}

