/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: system.c
Purpose: Stubs for a game system.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "system.h"

#include "log.h"

void System_Initialize(void)
{
    log_init();

    log_message("System:Initialize\n");
}

void System_Exit(void)
{
    log_message("System:Exit\n");
    log_close();
}

