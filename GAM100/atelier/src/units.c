#include "units.h"

// This is adding it before the tail, instead of after. Hmmm. Must fix.
unit * create_unit(const enum UNIT_TYPE type, const enum ELEMENT aspect, const int power, unit * parent)
{
	unit * new_unit = (unit*)malloc(sizeof(unit));

	assert(new_unit != NULL);

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

unit *get_tail(unit *head)
{
	if (head != NULL && head->next != NULL)
	{
		return get_tail(head->next);
	}

	return(head);
}

void append_unit(unit *head, unit *to_append)
{
	if (head != NULL)
	{
		if (head->next != NULL)
		{
			append_unit(head->next, to_append);
		}
		else
		{
			to_append->next = head->next;
			to_append->prev = head;
			head->next = to_append;
		}
	}
	else
	{
		head = to_append;
	}
}

unit *remove_unit(unit *to_remove)
{
	if (to_remove != NULL)
	{
		unit *removed = to_remove;

		if (removed->next == NULL && removed->prev == NULL)
		{
			to_remove = NULL;

			return removed;
		}

		if (removed->prev != NULL)
		{
			removed->prev->next = removed->next;
		}
		
		if (removed->next != NULL)
		{
			removed->next->prev = removed->prev;
		}

		to_remove = removed->next;

		return removed;
	}

	return NULL;
}

BOOL move_unit(unit *new_pool, unit *to_move)
{
	if (new_pool != NULL)
	{
		append_unit(new_pool, remove_unit(to_move));
	}
	else
	{
		new_pool = remove_unit(to_move);
	}

	return(TRUE);
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

void display_units(const unit * head)
{
	if (head)
	{
		// Disable this display for now, since it's technically unused.
#if 0
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
			case SOURCE:
				printf("Source/");
				break;
			case RESULT:
				printf("Result/");
				break;
			default:
				printf("ERR: Type case met default in display_units.\n");
		}
#endif
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
				printf("ERR: Element case met default in display_units.\n");
		}

		printf("(%d) ", head->power);

		display_units(head->next);
	}
	else
	{
		printf("\n");
	}
}

unit calculate_stack(const unit *head, const enum ELEMENT current_element, const int current_power)
{
	if (head != NULL)
	{
		switch (head->aspect)
		{
			case FIRE:
				if (WOOD == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power + head->power);
				}
				else if (WATER == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power - head->power);
				}
				else
				{
					// Bleed off 10 power.
					return calculate_stack(head->next, head->aspect, current_power - 10);
				}
				
				break;
			case EARTH:
				if (METAL == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power + head->power);
				}
				else if (WOOD == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power - head->power);
				}
				else
				{
					// Bleed off 10 power.
					return calculate_stack(head->next, head->aspect, current_power - 10);
				}
				
				break;
			case METAL:
				if (EARTH == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power + head->power);
				}
				else if (FIRE == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power - head->power);
				}
				else
				{
					// Bleed off 10 power.
					return calculate_stack(head->next, head->aspect, current_power - 10);
				}
				
				break;
			case WATER:
				if (METAL == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power + head->power);
				}
				else if (FIRE == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power - head->power);
				}
				else
				{
					// Bleed off 10 power.
					return calculate_stack(head->next, head->aspect, current_power - 10);
				}
				
				break;
			case WOOD:
				if (WATER == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power + head->power);
				}
				else if (METAL == current_element)
				{
					return calculate_stack(head->next, head->aspect, current_power - head->power);
				}
				else
				{
					// Bleed off 10 power.
					return calculate_stack(head->next, head->aspect, current_power - 10);
				}
				
				break;
			default:
				printf("ERR: Default case hit in calculate_stack function.\n");
		}
	}
	unit current_data;

	current_data.type = RESULT;
	current_data.aspect = current_element;
	current_data.power = current_power;

	current_data.next = NULL;
	current_data.prev = NULL;

	return current_data;
}

unit *get_unit(unit *head, const int index)
{
	if (head != NULL && index >= 0)
	{
		return get_unit(head->next, index - 1);
	}

	return head;
}

void destroy_all_units(unit * head)
{
	while (head != NULL)
	{
		assert(head->prev == NULL);
		destroy_unit(head);
	}
}

