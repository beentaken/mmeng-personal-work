/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment.cpp
Purpose: Implementation for wrapper for first assignment.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_2
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "assignment.hpp"
#include "Utilities.h"
#include <cmath>

namespace
{
    Mat3 translate(int x, int y)
    {
        Mat3 to_return(Mat3::Identity());

        to_return(0, 2) = static_cast<float>(x);
        to_return(1, 2) = static_cast<float>(y);

        return(to_return);
    }

    Mat3 rotate(float angle)
    {
        Mat3 to_return(Mat3::Identity());

        angle /= 180.0f/static_cast<float>(PI); // Convert to radians.

        to_return(0, 0) = std::cos(angle);
        to_return(1, 1) = std::cos(angle);
        to_return(0, 1) = -std::sin(angle);
        to_return(1, 0) = std::sin(angle);

        return(to_return);
    }

    Mat3 scale(float x, float y)
    {
        Mat3 to_return(Mat3::Identity());

        to_return(0, 0) = x;
        to_return(1, 1) = y;

        return(to_return);
    }
}

Assignment::Assignment()
    :num_triangles(4), triangles(num_triangles), axis(), camera_width(800), camera_height(600)
{
    myCreateTriangles();
    myCalculateCameraToViewport();

    axis.reserve(2);
    myCreateAxis();
}

void Assignment::drawScene()
{
    for (int i = 0; i < num_triangles; ++i)
    {
        triangles[i].draw(myCameraToViewport);
    }

    for (unsigned i = 0; i < axis.size(); ++i)
    {
        axis[i].draw(myCameraToViewport);
    }
}

void Assignment::myCreateTriangles()
{
    // Triangle 1:
    triangles[0].applyTransform(translate(100, 100));
    triangles[0].applyTransform(scale(10, 10));
    triangles[0].setColor(255, 0, 0);

    // Triangle 2:
    triangles[1].applyTransform(translate(-100, 100));
    triangles[1].applyTransform(rotate(45));
    triangles[1].applyTransform(scale(10, 10));
    triangles[1].setColor(0, 255, 0);

    // Triangle 3:
    triangles[2].applyTransform(translate(100, -100));
    triangles[2].applyTransform(scale(5, 10));
    triangles[2].setColor(0, 0, 255);
    
    // Triangle 4:
    triangles[3].applyTransform(translate(-100, -100));
    triangles[3].applyTransform(rotate(60));
    triangles[3].applyTransform(scale(10, 5));
    triangles[3].setColor(128, 128, 128);
}

void Assignment::myCreateAxis()
{
    Color black = { 0, 0, 0 };
    // X axis
    Mat3 x_left, x_right;
    x_left = x_right = Mat3::Identity();

    x_left(0, 0) = -200;
    x_left(1, 1) = 0;

    x_right(0, 0) = -x_left(0, 0);
    x_right(1, 1) = 0;

    axis.push_back(Line(x_left, x_right, black));

    Mat3 y_bottom, y_top;
    y_bottom = y_top = Mat3::Identity();

    y_bottom(0, 0) = y_top(0, 0) = 0;

    y_bottom(1, 1) = -200;
    y_top(1, 1) = -y_bottom(1, 1);

    axis.push_back(Line(y_bottom, y_top, black));
}

void Assignment::myCalculateCameraToViewport()
{
    // Normalize manually while I write a float/int combo matrix system.
    Matrix<3, 3, float> current, temp;

    current(0, 0) = static_cast<float>(WIDTH) / static_cast<float>(camera_width);
    current(1, 1) = -static_cast<float>(HEIGHT) / static_cast<float>(camera_height); // Flipped axis.
    current(2, 2) = 1.0f;

    // Build a translation matrix to relocate the origin.
    temp(0, 0) = 1.0f;
    temp(1, 1) = 1.0f;
    temp(2, 2) = 1.0f;

    temp(0, 2) = static_cast<float>(WIDTH)/ 2;
    temp(1, 2) = static_cast<float>(HEIGHT)/ 2;

    myCameraToViewport = temp * current;
}

