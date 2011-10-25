/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: level2.c
Purpose: Implementation for the first level state.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "level2.h"
#include "stdlib.h" /* malloc, free, abort */
#include "state.h" /* struct State */
#include "log.h" /* log_message */
#include "string.h" /* strcpy */
#include "stdio.h" /*fopen, fscanf, fclose */

struct level2_t
{
    struct state_t myState;

    int counter;
    int lives;
};

static States level2_load(void* this_ptr)
{
    const char* filename = "Level2_Lives.txt";
    FILE* data = fopen(filename, "rt");

    log_message(((State)this_ptr)->name);
    log_message(":Load\n");

    if(NULL == data)
    {
        log_message("ERROR: Could not open ");
        log_message(filename);
        log_message(".\n");

        abort();
    }

    /* TODO: Load lives from file. */
    if (EOF == fscanf(data, "%d", &((Level2)this_ptr)->lives))
    {
        log_message("ERROR: Could not read lives from file.\n");
        abort();
    }

    fclose(data);

    return(OK);
}

static States level2_init(void* this_ptr)
{
    FILE* data = fopen("Level2_Counter.txt", "rt");
    log_message(((State)this_ptr)->name);
    log_message(":Initialize\n");

    if (NULL == data)
    {
        log_message("ERROR: Couldn't open level 2 counter.\n");
        abort();
    }
    
    /* Load counter from file. */
    if (EOF == fscanf(data, "%d", &((Level2)this_ptr)->counter))
    {
        log_message("ERROR: Could not read level 2 counter data from file.\n");
        abort();
    }

    fclose(data);

    return(OK);
}

static States level2_update(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Update\n");

    --((Level2)this_ptr)->counter;

    if (((Level2)this_ptr)->counter == 0)
    {
        --((Level2)this_ptr)->lives;

        /* Do stuff. */
        if (((Level2)this_ptr)->lives > 0)
        {
            /* Restart level. */
            return(RESTART);
        }
        else
        {
            return(QUIT);
        }
    }

    return(OK);
}

static States level2_draw(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Draw\n");

    return(OK);
}

static States level2_free(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Free\n");

    return(OK);
}

static States level2_unload(void* this_ptr)
{
    log_message(((State)this_ptr)->name);
    log_message(":Unload\n");

    free(((State)this_ptr)->name);
    free(this_ptr);

    return(OK);
}

Level2 create_level2(void)
{
    Level2 new_level2 = (Level2)malloc(sizeof(struct level2_t));

    new_level2->myState.name = (char*)malloc(10*sizeof(char));
    strcpy(new_level2->myState.name, "Level2");
    new_level2->myState.load = &level2_load;
    new_level2->myState.initialize = &level2_init;
    new_level2->myState.update = &level2_update;
    new_level2->myState.draw = &level2_draw;
    new_level2->myState.free = &level2_free;
    new_level2->myState.unload = &level2_unload;
    new_level2->myState.this_ptr = (State)new_level2;

    return(new_level2);
}

