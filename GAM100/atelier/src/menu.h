#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include "definitions.h"
#include "parser.h"
#include "state.h"

/* Prints a series of credit strings.
 *
 * Preconditions: None.
 * Postconditions: Credit strings have been printed to the screen.
 */
void print_credits();

/* Displays the main menu.
 *
 * Preconditions: current points to a valid, initialized gamestate.
 * Postconditions: current is modified based on user input.
 *
 * Returns: FALSE if the user enters a quit command, TRUE otherwise.
 */
BOOL menu(struct GAMESTATE *current);

#endif

