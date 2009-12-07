/* This file should not contain more than what is needed to initialize
 * and set up a basic game loop.
 */

#include <stdio.h>

#include "game.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		puts(argv[1]);
	}

	while(game_loop());
	return 0;
}

