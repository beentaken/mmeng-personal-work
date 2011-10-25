/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: triangle.hpp
Purpose: Prototypes for a triangle.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point4.h"
#include "Vector4.h"

struct Triangle
{
    public:

        // Vertex positions.
        Point4 p0;
        Point4 p1;
        Point4 p2;

        // Vertex colors.
        Vector4 c0;
        Vector4 c1;
        Vector4 c2;

        // Texcoords.
        Vector4 t0;
        Vector4 t1;
        Vector4 t2;
};

#endif // TRIANGLE_H

