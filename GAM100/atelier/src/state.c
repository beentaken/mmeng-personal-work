#include "state.h"

void initialize_game_state(struct GAMESTATE *current)
{
	current->current_state = MENU;
	current->current_line = 0;

	int i;

	// Start i from 1 because we'll put a default value into the first
	// unit to start the player off.
	for (i = 1; i < MAX_LINES; ++i)
	{
		current->lines[i] = NULL;
	}

	current->lines[0] = create_unit(SOURCE, WATER, 100, NULL);
}

