/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: circle.hpp
Purpose: Prototypes for a circle.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "matrix.hpp"
#include "drawable.hpp"

class Circle : public Drawable
{
    public:
		Circle(Vec3 newcenter, int newradius, Color newcolor);
        virtual void draw(const Matrix<3, 3, float>& toViewport);

    private:
        Vec3 center;
        int radius;
		Color color;
};

#endif // CIRCLE_H

