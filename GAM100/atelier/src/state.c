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

	current->pool = create_unit(DIODE, FIRE, 100, NULL);
	append_unit(current->pool, create_unit(DIODE, WOOD, 100, NULL));
	append_unit(current->pool, create_unit(DIODE, METAL, 100, NULL));
	append_unit(current->pool, create_unit(DIODE, FIRE, 100, NULL));
	append_unit(current->pool, create_unit(DIODE, WOOD, 150, NULL));
	append_unit(current->pool, create_unit(DIODE, EARTH, 200, NULL));
	append_unit(current->pool, create_unit(DIODE, FIRE, 300, NULL));
	append_unit(current->pool, create_unit(DIODE, METAL, 100, NULL));
	append_unit(current->pool, create_unit(DIODE, EARTH, 100, NULL));
}

