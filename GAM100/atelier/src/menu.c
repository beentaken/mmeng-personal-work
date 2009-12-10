#include "menu.h"

void print_credits()
{
	printf("All content © 2009 DigiPen (USA) Corporation, all rights reserved.\n");
	printf("President: Claude Comair\n");
	printf("Executive Producers: Doug Schilling, Elie Abi Chahine\n");

	printf("Designer: Marcus Meng\n\n");
}

void print_help()
{
	printf("Instructions:\n\n");

	printf("Try to build a system where you have sufficient power output at the\n"
		" end of a set of chains to win. The elemental effects of each component\n"
		" will influence how much power is lost or gained per step.\n\n");
}

BOOL menu(struct GAMESTATE *current)
{
	printf("\nAtelier\n\n");

	printf("Commands:\n");
	printf("n: New game.\n");
	printf("?: Help.\n");
	printf("a: Credits.\n");
	printf("q: Quit.\n\n");

	struct COMMAND current_order;

	current_order = get_command();

	switch(current_order.order)
	{
		case NEW_GAME:
			current->current_state = GAME;
			return TRUE;
			break;
		case QUIT:
			return FALSE;
			break;
		case HELP:
			print_help();
			break;
		case CREDITS:
			print_credits();
			break;
		case INVALID:
			printf("Invalid command.\n");
			break;
		default:
			// This shouldn't ever happen.
			printf("ERR: Default case in menu function hit.\n");
			return FALSE;
	}

	return TRUE;
}

