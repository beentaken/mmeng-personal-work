/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: triangle_model.hpp
Purpose: Prototypes for a transformable triangle model.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_2
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef TRIANGLE_MODEL_H
#define TRIANGLE_MODEL_H

#include "matrix.hpp"
#include "line.hpp"

class Triangle
{
    public:
        Triangle();

        void draw(const Mat3 &viewport) const;
        void applyTransform(const Matrix<3, 3, float> &transform);
        void setColor(unsigned char r, unsigned char g, unsigned char b);

    private:
        Matrix<3, 3, float> points[3];
        Matrix<3, 3, float> transformation;

        Color myColor;
};

#endif // TRIANGLE_MODEL_H

