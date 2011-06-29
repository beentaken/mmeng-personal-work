/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: triangle_model.cpp
Purpose: Implementation for a transformable triangle model.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_2
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "triangle_model.hpp"
#include "line.hpp"

Triangle::Triangle()
    :transformation(Matrix<3, 3, float>::Identity())
{
    // (0, 1)
    points[0](0, 0) = 0;
    points[0](1, 0) = 1;
    points[0](2, 0) = 1;

    // (-1, -1)
    points[1](0, 0) = -1;
    points[1](1, 0) = -1;
    points[1](2, 0) = 1;


    // (1, -1)
    points[2](0, 0) = 1;
    points[2](1, 0) = -1;
    points[2](2, 0) = 1;

}

void Triangle::applyTransform(const Matrix<3, 3, float> &transform)
{
    transformation *= transform;
}

void Triangle::setColor(unsigned char r, unsigned char g, unsigned char b)
{
    myColor.r = r;
    myColor.g = g;
    myColor.b = b;
}

void Triangle::draw(const Mat3 &viewport) const
{
    Line first(points[0], points[1], myColor);
    Line second(points[1], points[2], myColor);
    Line third(points[2], points[0], myColor);

    first.draw(viewport * transformation);
    second.draw(viewport * transformation);
    third.draw(viewport * transformation);
}

