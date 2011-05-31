/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: gamestatelist.h
Purpose: Lists a series of enumerated constants that states may use.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef GAMESTATELIST_H
#define GAMESTATELIST_H

enum states_t
{
    OK = 0,
    ERROR,
    END,
    RUNNING,
    RESTART,
    QUIT
};

typedef enum states_t States;

#endif /* GAMESTATELIST_H */

