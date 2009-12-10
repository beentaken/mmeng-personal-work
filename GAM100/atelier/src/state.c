#include "state.h"

void initialize_game_state(struct GAMESTATE *current)
{
	current->current_state = MENU;
	current->current_line = 0;

	current->lines[0] = create_unit(SOURCE, WATER, 100, NULL);
	current->lines[1] = create_unit(SOURCE, FIRE, 200, NULL);
	current->lines[2] = create_unit(SOURCE, WOOD, 160, NULL);
	current->lines[3] = create_unit(SOURCE, EARTH, 140, NULL);
	current->lines[4] = create_unit(SOURCE, METAL, 400, NULL);

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

