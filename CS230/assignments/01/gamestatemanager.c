/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: gamestatemanager.c
Purpose: Implementation for a rudimentary game state manager.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "gamestatemanager.h"
#include "log.h"

#include <stdlib.h> /* NULL */

static State current_state;

void GSM_Initialize(State initial)
{
    log_message("GSM:Initialize\n");

    current_state = NULL;
    
    GSM_Update(initial);
}

void GSM_Update(State new_state)
{
    if (NULL != current_state)
    {
        (*current_state->free)(current_state);
        (*current_state->unload)(current_state);
    }

    log_message("GSM:Update\n");

    current_state = new_state;

    (*current_state->load)(current_state);
    (*current_state->initialize)(current_state);
}

/* Why not make our main function not have to worry about this stuff at all.
 * So much more pleasant, ne?
 */
void GSM_Restart(void)
{
    (*current_state->free)(current_state);
    (*current_state->initialize)(current_state);
}

States GSM_RunFrame(void)
{
    States result;
    result = (*current_state->update)(current_state);
    (*current_state->draw)(current_state);

    return(result);
}

void GSM_Exit(void)
{
    (*current_state->free)(current_state);
    (*current_state->unload)(current_state);
}

