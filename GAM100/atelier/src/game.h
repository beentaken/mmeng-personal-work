/* Contains the core engine functions.
 */

#ifndef GAME_H
#define GAME_H

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "definitions.h"
#include "state.h"
#include "parser.h"
#include "units.h"
#include "menu.h"

/* This should be called once per cycle of the game loop.
 * Precondition: head contains a pointer to the source unit.
 * Postcondition: head and tail are modified as appropriate to the commands
 * 	entered.
 *
 * Returns: FALSE if the user selects a "quit" option, TRUE otherwise.
 */
bool game_loop(struct GAMESTATE *current);

/* This takes an array containing pointers to the heads of all the linked
 * lists, and prints all the lists preceded by an index.
 *
 * Precondition: None.
 * Postcondition: The various data contained in the linked lists are printed.
 */
void print_all_lines(unit *head[], const int current_line, const int lines);

/* This function is run every loop while actually in-game.
 *
 * Precondition: current is a properly initialized gamestate;
 * Postcondition: User input is read, gamestate is updated based on commands.
 *
 * Returns: FALSE if the user selects the "quit" option, TRUE otherwise.
 */
bool in_game(struct GAMESTATE *current);

#endif

