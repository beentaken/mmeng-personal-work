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
	printf("\tWood feeds Fire;\n\tFire feeds Earth;\n\tEarth feeds Metal;\n"
		"\tMetal feeds Water;\n\tWater feeds Wood.\n\n");
	printf("\tWood restrains Earth;\n\tEarth restrains Water;\n\tWater restrains Fire;\n"
		"\tFire restrains Metal;\n\tMetal restrains Wood.\n\n");

	printf("The aspect of the power flow changes as it passes through the units.\n"
		"If the aspect of a power flow feeds the unit it passes through, the\n"
		"unit's power is added to the flow. If it restrains it, the unit's power\n"
		"is deducted from the flow.\n\n");
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

