#ifndef UNITS_H
#define UNITS_H

#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"

enum UNIT_TYPE
{
	DIODE, // Only lets power flow one way.
	GATE, // Modifies aspect of power moving through.
	RESISTOR // Reduces or inflames power moving through.
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

unit * create_unit(enum UNIT_TYPE type, enum ELEMENT aspect, int power, unit * parent);
BOOL destroy_unit(unit * to_destroy);
void display_units(unit * head);

// Internal stuff for cleanups and things. Should never be called on its own.
void destroy_all_units(unit * head);

#endif

