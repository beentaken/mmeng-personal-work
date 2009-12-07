/* Contains the core engine functions.
 */

#ifndef GAME_H
#define GAME_H

#include <assert.h>
#include <stdio.h>

#include "definitions.h"
#include "parser.h"
#include "units.h"

BOOL game_loop(unit * head, unit * tail);

#endif

