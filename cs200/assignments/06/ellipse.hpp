/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: ellipse.hpp
Purpose: Prototypes for an ellipse.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "matrix.hpp"
#include "drawable.hpp"

class Ellipse : public Drawable
{
    public:
		Ellipse(Vec3 newcenter, int newradius_a, int newradius_b, Color newcolor);
        virtual void draw(const Matrix<3, 3, float>& toViewport);

    private:
        Vec3 center;
        int radius_a;
		int radius_b;
		Color color;
};

#endif // ELLIPSE_H
