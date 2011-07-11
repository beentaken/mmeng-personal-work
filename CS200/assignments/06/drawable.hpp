/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: drawable.hpp
Purpose: Interface for a drawable geometry.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "matrix.hpp"

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};


class Drawable
{
    public:
        virtual void draw(const Matrix<3, 3, float>& toViewport) = 0;
};

#endif // DRAWABLE_H


