#include "units.h"

// This is adding it before the tail, instead of after. Hmmm. Must fix.
unit * create_unit(enum UNIT_TYPE type, enum ELEMENT aspect, int power, unit * parent)
{
	unit * new_unit = malloc(sizeof(unit));

	new_unit->type = type;
	new_unit->aspect = aspect;
	new_unit->power = power;

	if (parent != NULL)
	{
		new_unit->prev = parent;
		new_unit->next = parent->next;
		parent->next = new_unit;
	}
	else
	{
		new_unit->prev = NULL;
		new_unit->next = NULL;
	}

	return new_unit;
}

BOOL destroy_unit(unit * to_destroy)
{
	if (to_destroy)
	{
		to_destroy->prev->next = to_destroy->next;

		if (to_destroy->next)
		{
			if (to_destroy->prev)
			{
				to_destroy->next->prev = to_destroy->prev;
				to_destroy->prev->next = to_destroy->next;

				free(to_destroy);
			}
			else
			{
				unit *temp = to_destroy;
				to_destroy = to_destroy->next;

				free(temp);
			}

		}
		else
		{
			unit * temp = to_destroy;
			to_destroy = NULL;

			free(temp);
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void display_units(unit * head)
{
	if (head)
	{
		switch (head->type)
		{
			case DIODE:
				printf("Diode/");
				break;
			case GATE:
				printf("Gate/");
				break;
			case RESISTOR:
				printf("Resistor/");
				break;
			default:
				printf("ERR: Type case met default.\n");
		}

		switch (head->aspect)
		{
			case WOOD:
				printf("Wood");
				break;
			case FIRE:
				printf("Fire");
				break;
			case EARTH:
				printf("Earth");
				break;
			case METAL:
				printf("Metal");
				break;
			case WATER:
				printf("Water");
				break;
			default:
				printf("ERR: Element case met default.\n");
		}

		printf("(%d)\n", head->power);

		display_units(head->next);
	}
}

void destroy_all_units(unit * head)
{
	while (head != NULL)
	{
		destroy_unit(head);
	}
}

