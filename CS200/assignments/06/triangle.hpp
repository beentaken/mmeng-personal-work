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

#include "matrix.hpp"
#include "drawable.hpp"

class Triangle : public Drawable
{
    public:
		Triangle(const Vec3& point1, const Vec3& point2, const Vec3& point3);
        virtual void draw(const Mat3& toViewport);

    private:
        Vec3 p0;
        Vec3 p1;
        Vec3 p2;
};

#endif // TRIANGLE_H

