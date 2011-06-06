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
#include <cmath>

#include "matrix_transform.hpp"

using mat3t::translate;
using mat3t::rotate;
using mat3t::scale;

Assignment::Assignment()
    :num_triangles(4), triangles(num_triangles), axis(), camera_width(800), camera_height(600), myCam(camera_width, camera_height)
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

void Assignment::handleInput(int key)
{
    switch (key)
    {
        case 'x':
            myCam.turn(1);
            break;
        case 'z':
            myCam.turn(-1);
            break;
        case 'w':
            myCam.move(0, 1);
            break;
        case 's':
            myCam.move(0, -1);
            break;
        case 'a':
            myCam.move(-1, 0);
            break;
        case 'd':
            myCam.move(1, 0);
            break;
        case 'e':
            myCam.zoom(2);
            break;
        case 'q':
            myCam.zoom(1.0f/2);
            break;
    }

    myCalculateCameraToViewport();
}

void Assignment::myCalculateCameraToViewport()
{

    myCameraToViewport = translate(static_cast<float>(WIDTH) / 2, static_cast<float>(HEIGHT) / 2)
        * scale(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)) * myCam.getCameraTransform();
}

