#include "game.h"

/* Currently, this function contains a switch case to process commands that
 * the game recieves from the parser functions. It should assume that head
 * is a valid pointer to a defined unit.
 *
 * It should also check whether the victory condition has been met with the
 * set of units provided.
 */
BOOL game_loop(struct GAMESTATE *current)
{
	switch (current->current_state)
	{
		case MENU:
			return menu(current);
			break;
		case GAME:
			return in_game(current);
			break;
		default:
			// If we get here, there's a problem...
			return TRUE;
	}
}

void print_all_lines(unit * head[], const int current_line, const int lines)
{
	int i;

	for (i = 0; i < lines; ++i)
	{
		char marker;
		if (i == current_line)
			marker = '>';
		else
			marker = ' ';
		printf("%cLine %d: ", marker, i);
		display_units(head[i]);
	}

	unit end_value = calculate_stack(head[0]->next, head[0]->aspect, head[0]->power);

	for (i = 1; i < MAX_LINES; ++i)
	{
		end_value = calculate_stack(head[i], end_value.aspect, end_value.power);
	}

	printf("End value is ");
	display_units(&end_value);
}

void print_keys()
{
	printf("\n");
	printf("c: Create a new unit.\n");
	printf("d: Delete the last unit.\n");
	printf("s <number>: Switch to specified line.\n");
}

BOOL in_game(struct GAMESTATE *current)
{
	struct COMMAND current_order;

	printf("\nCurrent lines:\n");
	print_all_lines(current->lines, current->current_line, MAX_LINES);

	current_order = get_command();

	switch(current_order.order)
	{
		case QUIT:
			return FALSE;
		case HELP:
			print_keys();
		case CREATE:
			;
			// Create a unit and append it to the end of the list.
			// TODO: Make this work right!
			create_unit(DIODE, WOOD, current_order.value, current->lines[current->current_line]);

			break;
		case SWITCH_LINES:
			if (current_order.value >= 0 && current_order.value < MAX_LINES)
			{
				current->current_line = current_order.value;
			}
			else
			{
				printf("\nInvalid line number.\n");
			}

			break;
		case INVALID:
		default:
			printf("\nUnrecognized command.\n");
	}

	return TRUE;
}

