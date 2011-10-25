#ifndef UNITS_H
#define UNITS_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "definitions.h"

enum UNIT_TYPE
{
	SOURCE, // Each level starts out with one of these.
	DIODE, // Only lets power flow one way.
	GATE, // Modifies aspect of power moving through.
	RESISTOR, // Reduces or inflames power moving through.
	RESULT // Used when doing the end calculations.
};

/* Remember that:
 * Wood feeds Fire
 * Fire creates Earth
 * Earth bears Metal
 * Metal carries Water
 * Water nourishes Wood.
 *
 * And...
 * Wood parts Earth
 * Earth absorbs Water
 * Water quenches Fire
 * Fire melts Metal
 * Metal chops Wood
 */
enum ELEMENT
{
	WOOD,
	FIRE,
	EARTH,
	METAL,
	WATER
};

// Functions as a double-linked list.
struct UNIT_STRUCT
{
	enum UNIT_TYPE type;
	enum ELEMENT aspect;

	int power;

	struct UNIT_STRUCT * next;
	struct UNIT_STRUCT * prev;
};

typedef struct UNIT_STRUCT unit;

// Functions to manipulate stuff.

/* Creates a unit.
 *
 * Preconditions: parent must point to a valid, existing unit, or NULL.
 * Postconditions: A new unit is created in memory. parent->null, if exists, now points to this unit.
 *
 * Returns: A pointer to the newly-created unit.
 */
unit * create_unit(const enum UNIT_TYPE type, const enum ELEMENT aspect, const int power, unit * parent);

/* Appends a unit to the end of the list that head is part of.
 *
 * Preconditions: to_append is a valid, non-NULL unit.
 * Postconditions: to_append is the last node in the linked list, to_append->next is NULL.
 */
void append_unit(unit * head, unit * to_append);

/* Finds the tail of a list.
 *
 * Preconditions: None.
 * Postconditions: head is unchanged.
 *
 * Returns: A pointer to the last node in the linked list head, NULL if it does not exist.
 */
unit *get_tail(unit *head);

/* Finds a unit at a specified index.
 *
 * Preconditions: None.
 * Postcondition: The list is unchanged.
 *
 * Returns: A pointer to the unit in the index specified, NULL otherwise.
 */
unit *get_unit(unit *head, const int index);

/* Finds how long the linked list is.
 *
 * Preconditions: head is either a valid linked list node or NULL.
 * Postconditions: head is unchanged.
 *
 * Returns: The total index size of the list.
 */
int get_pool_size(const unit *head);

/* Removes a unit from the pool it is in.
 *
 * Preconditions: to_remove is a non-NULL, valid unit pointer.
 * Postconditions: to_remove is no longer pointed to in its original pool,
 * 		and to_remove->next and to_remove->prev point to NULL.
 *
 * Returns: A pointer to the unit that was removed, NULL if the unit did not exist.
 */
unit *remove_unit(unit *to_remove);

/* Moves a unit, removing it from its current pool and appending it to the new pool.
 *
 * Preconditions: to_remove is a valid, non-NULL unit pointer.
 * Postconditions: to_remove is no longer in its original pool, and exists at the end of new_pool.
 *
 * Returns: TRUE if the move succeeded, FALSE otherwise.
 */
bool move_unit(unit *new_pool, unit *to_move);

/* Destroys a unit.
 *
 * Preconditions: to_destroy is a valid, non-NULL unit pointer.
 * Postconditions: to_destroy is NULL, and the memory it pointed to is deallocated.
 *
 * Returns: TRUE if the deallocation succeeded, FALSE otherwise.
 */
bool destroy_unit(unit * to_destroy);

/* Displays a formatted pool with indices.
 *
 * Preconditions: None.
 * Postconditions: All units are displayed with indices.
 */
void display_pool(const unit *head, const int index);

/* Displays all the units in a pool.
 *
 * Preconditions: None.
 * Postconditions: Displays all the units in a pool, seperated by spaces. Displays a newline at the end.
 */
void display_units(const unit * head);

/* Goes through a linked list of units and finds out how much power remains at
 * the end of the line.
 *
 * Preconditions: head is either defined or NULL.
 * Postconditions: None.
 *
 * Returns: A unit containing the calculated values, with both pointers NULL.
 */
unit calculate_stack(const unit *head, const enum ELEMENT current_element, const int current_power);

/* Destroys all units in a given pool.
 *
 * Preconditions: None.
 * Postconditions: All units in a pool are deallocated and the pointers are
 * 		set to NULL.
 */
void destroy_pool(unit * head);

#endif

