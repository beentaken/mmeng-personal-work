/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: main.c
Purpose: Driver program for part 1 of assignment 1.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "state.h"
#include "level1.h"
#include "level2.h"
#include "system.h"
#include "gamestatemanager.h"
#include "input.h"

int main(void)
{
    int i = 0;
    States result;
    State level[2];
    State current;

    System_Initialize();

    level[0] = (State)create_level1();
    level[1] = (State)create_level2();

    current = level[i];

    GSM_Initialize(current);

    /* It's gameloop time! */
    do
    {
        Input_Handle();
        
        result = GSM_RunFrame();

        switch (result)
        {
            case RESTART:
                GSM_Restart();
                break;
            case END:
                ++i;
                current = level[i];

                GSM_Update(level[i]); /* the heck is this for. */

                break;
            default:
                break;
        }
    } while (result != QUIT && result != ERROR);
    
    GSM_Exit();

    System_Exit();

    return 0;
}

