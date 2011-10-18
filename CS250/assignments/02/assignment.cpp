/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment.cpp
Purpose: Implementation for wrapper for first assignment.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_3
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "assignment.hpp"
#include "Utilities.h"

#include <iostream>

#include "render.hpp"

Assignment::Assignment()
{
}

void Assignment::drawScene()
{
    Triangle blah;
    blah.p0.x = 40;
    blah.p0.y = 40;

    blah.p1.x = 80;
    blah.p1.y = 40;

    blah.p2.x = 0;
    blah.p2.y = 0;

    blah.c0.r = 255;
    blah.c0.g = 255;
    blah.c0.b = 0;
    
    blah.c1.r = 255;
    blah.c1.g = 255;
    blah.c1.b = 0;
    
    blah.c1.r = 255;
    blah.c1.g = 255;
    blah.c1.b = 0;

    Renderer.addDrawable(blah);
}


void Assignment::handleInput(int key, int /* x */, int /* y */ )
{
    switch (key)
    {
        default:
            std::cout << key << " was pressed." << std::endl;
    }
        
}

