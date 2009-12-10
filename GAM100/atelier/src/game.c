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

BOOL check_victory(unit *head[], const int lines)
{
	int i;

	unit end_value = calculate_stack(head[0]->next, head[0]->aspect, head[0]->power);

	for (i = 1; i < lines; ++i)
	{
		end_value = calculate_stack(head[i], end_value.aspect, end_value.power);
	}

	if (end_value.power > 999)
	{
		return TRUE;
	}

	return FALSE;
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

	for (i = 1; i < lines; ++i)
	{
		end_value = calculate_stack(head[i], end_value.aspect, end_value.power);
	}

	printf("End value is ");
	display_units(&end_value);
}

void print_keys()
{
	printf("\n");
	printf("c: Move the next unit in the pool to the current line.\n");
	printf("r: Remove the last unit, returning it to the pool.\n");
	printf("s <number>: Switch to specified line.\n");
}

BOOL in_game(struct GAMESTATE *current)
{
	struct COMMAND current_order;

	printf("\nCurrent pool:\n");
	display_units(current->pool);

	printf("\nCurrent lines:\n");
	print_all_lines(current->lines, current->current_line, MAX_LINES);

	// Check to see if we've won!
	if (check_victory(current->lines, MAX_LINES))
	{
		current->current_state = MENU;

		printf("Victory condition reached, sequence has exceeded 1000 power.\n");

		return TRUE;
	}

	current_order = get_command();

	switch(current_order.order)
	{
		case QUIT:
			return FALSE;
		case HELP:
			print_keys();
			break;
		case CREATE:
			;
			// Create a unit and append it to the end of the list.
//			append_unit(current->lines[current->current_line], create_unit(DIODE, WOOD, current_order.value, NULL));
			move_unit(current->lines[current->current_line], current->pool);
			
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
		case REMOVE:
			move_unit(current->pool, get_tail(current->lines[current->current_line]));

			break;
		case INVALID:
		default:
			printf("\nUnrecognized command.\n");
	}

	return TRUE;
}

