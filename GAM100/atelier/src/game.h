/* Contains the core engine functions.
 */

#ifndef GAME_H
#define GAME_H

#include <assert.h>
#include <stdio.h>

#include "definitions.h"
#include "parser.h"
#include "units.h"

/* This should be called once per cycle of the game loop.
 * Precondition: head contains a pointer to the source unit.
 * Postcondition: head and tail are modified as appropriate to the commands
 * 	entered.
 *
 * Returns: FALSE if the user selects a "quit" option, TRUE otherwise.
 */
BOOL game_loop(unit * head, unit * tail);

#endif

