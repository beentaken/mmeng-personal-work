#include "game.h"

/* Currently, this function contains a switch case to process commands that
 * the game recieves from the parser functions. It should assume that head
 * is a valid pointer to a defined unit.
 *
 * It should also check whether the victory condition has been met with the
 * set of units provided.
 */
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
			// tail should only be NULL if this is the first time
			// adding something to the linked list. In other
			// words, this should only ever work once per game.
			if (tail == NULL)
			{
				tail = create_unit(DIODE, WOOD, current_order.value, head);
			}
			else
			{
				tail = create_unit(DIODE, WOOD, current_order.value, tail);
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

