/* Contains functions for parsing incoming commands and calling other
 * functions based on that as appropriate.
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "definitions.h"

/* Gets user input and parses it.
 *
 * Preconditions: None.
 * Postconditions: None.
 *
 * Returns: A COMMAND struct containing values representing the commands the
 * 		user entered.
 */
struct COMMAND get_command(void);

#endif

