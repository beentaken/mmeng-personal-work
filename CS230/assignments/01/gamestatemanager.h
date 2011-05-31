/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: gamestatemanager.h
Purpose: Prototypes for a rudimentary game state manager.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef GAMESTATE_MANAGER_H
#define GAMESTATE_MANAGER_H

#include "state.h"

void GSM_Initialize(State initial);
void GSM_Update(State new_state);

void GSM_Restart(void);
States GSM_RunFrame(void);
void GSM_Exit(void);

#endif /* GAMESTATE_MANAGER_H */

