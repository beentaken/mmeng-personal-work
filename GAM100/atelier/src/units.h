#ifndef UNITS_H
#define UNITS_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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

unit * create_unit(const enum UNIT_TYPE type, const enum ELEMENT aspect, const int power, unit * parent);
void append_unit(unit * head, unit * to_append);
BOOL destroy_unit(unit * to_destroy);
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

// Internal stuff for cleanups and things. Should never be called on its own.
void destroy_all_units(unit * head);

#endif

