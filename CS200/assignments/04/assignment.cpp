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
    :points(), lines(), camera_width(800), camera_height(600), myCam(camera_width, camera_height)
{
    myCalculateCameraToViewport();
}

void Assignment::drawScene()
{
    for (unsigned i = 0; i < lines.size(); ++i)
    {
        lines[i].draw(Mat3::Identity()); // No viewport matrix.
    }
}


void Assignment::handleInput(int key, int x, int y)
{
    switch (key)
    {
        case 'c':
            lines.clear();
            break;
        case GLUT_LEFT_BUTTON:
            Mat3 new_point;
            new_point(0,0) = static_cast<float>(x);
            new_point(1,1) = static_cast<float>(y);
            new_point(2,2) = 1;
            points.push_back(new_point);
            break;
    }

    if (points.size() == 2)
    {
        Color black = {0, 0, 0};
        lines.push_back(Line(points.front(), points.back(), black));
        points.clear();
    }

    myCalculateCameraToViewport();
}

void Assignment::myCalculateCameraToViewport()
{

    myCameraToViewport = translate(static_cast<float>(WIDTH) / 2, static_cast<float>(HEIGHT) / 2)
        * scale(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)) * myCam.getCameraTransform();
}

