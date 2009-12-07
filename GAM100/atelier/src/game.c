#include "game.h"

BOOL game_loop(unit * head, unit * tail)
{
	struct COMMAND current_order;

	display_units(head);

	current_order = get_command();

	switch(current_order.order)
	{
		case QUIT:
			return FALSE;
		case CREATE:
			if (tail == NULL)
			{
				tail = create_unit(DIODE, WOOD, current_order.value, head);
			}
			else
			{
				create_unit(DIODE, WOOD, current_order.value, tail);
			}
			assert(tail != NULL);
			assert(head != NULL);

			break;
		case INVALID:
		default:
			printf("Unrecognized command.\n");
	}

	return TRUE;
}

