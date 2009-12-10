/* This file should not contain more than what is needed to initialize
 * and set up a basic game loop.
 */

#include <stdio.h>
#include <string.h>

#include "game.h"
#include "state.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		int i;

		for (i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i], "--debug") == 0)
			{
				printf("Debug mode.\n");
			}
			else if (strcmp(argv[i], "--help") == 0)
			{
				printf("%s\n\n\t--help\tShow help.\n\t--debug\tEnable debug mode.",
					argv[0]);
			}
		}
	}

	struct GAMESTATE current_gamestate;

	initialize_game_state(&current_gamestate);
	// Hardcoding an initial setup. This will change once an actual level
	// system is implemented.

	while(game_loop(&current_gamestate));

	// Do some cleanup before we leave. Can't have the OS steal all the
	// fun, after all, right?
	// destroy_game_state(&current_gamestate);

	return 0;
}

