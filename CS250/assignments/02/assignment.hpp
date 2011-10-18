/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment.hpp
Purpose: Prototypes for an assignment class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef CS200_ASSIGNMENT_H
#define CS200_ASSIGNMENT_H

#include <vector>
#include <deque>
#include "Matrix4.h"
#include "Vector4.h"

class Assignment
{
    public:
        Assignment();

        void drawScene();

        void handleInput(int key, int x = 0, int y = 0);

    private:

};

#endif // CS200_ASSIGNMENT_H

