#include "game.h"

BOOL game_loop()
{
	struct COMMAND current_order = get_command();

	if (QUIT == current_order.order)
	{
		return FALSE;
	}

	return TRUE;
}

