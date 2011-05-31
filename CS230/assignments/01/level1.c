/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: level1.c
Purpose: Implementation for the second level state.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "level1.h"
#include "stdlib.h" /* malloc, free, abort */
#include "state.h" /* struct State */
#include "log.h" /* log_message */
#include "string.h" /* strcpy */
#include "stdio.h" /* fopen, fscanf, fclose */

struct level1_t
{
    struct state_t myState;

    int counter;
};

static States level1_load(void* this_ptr)
{
    FILE* data = fopen("Level1_Counter.txt", "rt");
    log_message(((State)this_ptr)->name);
    log_message(":Load\n");

    if (NULL == data)
    {
        log_message("ERROR: Could not open Level1_Counter.txt.\n");
        abort();
    }

    if(EOF == fscanf(data, "%d", &((Level1)this_ptr)->counter))
    {
        log_message("ERROR: Read end of file in Level1_Counter.txt.\n");
        abort();
    }

    fclose(data);

    return(OK);
}

static States level1_init(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Initialize\n");

    return(OK);
}

static States level1_update(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Update\n");

    --((Level1)this_ptr)->counter;

    if (((Level1)this_ptr)->counter == 0)
    {
        return(END);
    }

    return(OK);
}

static States level1_draw(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Draw\n");

    return(OK);
}

static States level1_free(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Free\n");

    return(OK);
}

static States level1_unload(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Unload\n");

    free(((State)this_ptr)->name);
    free(this_ptr);

    return(OK);
}

Level1 create_level1(void)
{
    Level1 new_level1 = malloc(sizeof(struct level1_t));

    new_level1->myState.name = malloc(10 * sizeof(char));
    strcpy(new_level1->myState.name, "Level1");
    new_level1->myState.load = &level1_load;
    new_level1->myState.initialize = &level1_init;
    new_level1->myState.update = &level1_update;
    new_level1->myState.draw = &level1_draw;
    new_level1->myState.free = &level1_free;
    new_level1->myState.unload = &level1_unload;
    new_level1->myState.this_ptr = (State)new_level1;

    return(new_level1);
}

