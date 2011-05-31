/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: state.h
Purpose: Declaration of a struct container to hold state functions.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef STATE_H
#define STATE_H

#include "gamestatelist.h"

typedef States (*state_fun)(void*);
typedef struct state_t* State;

struct state_t
{
    char* name;

    state_fun load;
    state_fun initialize;
    state_fun update;
    state_fun draw;
    state_fun free;
    state_fun unload;

    State this_ptr;
};

#endif /* STATE_H */

