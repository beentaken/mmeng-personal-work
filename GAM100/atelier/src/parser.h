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

void test_print(void);
struct COMMAND get_command(void);

#endif

