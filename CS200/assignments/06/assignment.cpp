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
#include "circle.hpp"
#include "ellipse.hpp"
#include "line.hpp"
#include "triangle.hpp"

#include "matrix_transform.hpp"

using mat3t::translate;
using mat3t::rotate;
using mat3t::scale;

Assignment::Assignment()
    :current_mode(TRIANGLE), points(), lines(), camera_width(800), camera_height(600), myCam(camera_width, camera_height)
{
    myCalculateCameraToViewport();
}

void Assignment::drawScene()
{
    for (unsigned i = 0; i < lines.size(); ++i)
    {
        lines[i]->draw(Mat3::Identity()); // No viewport matrix.
    }
}


void Assignment::handleInput(int key, int x, int y)
{
    switch (key)
    {
        case 'r':
            clearDrawables();
            break;
        case 'c':
            current_mode = CIRCLE;
            break;
        case 'e':
            current_mode = ELLIPSE;
            break;
        case 'l':
            current_mode = LINE;
            break;
        case 't':
            current_mode = TRIANGLE;
            break;
        case GLUT_LEFT_BUTTON:
            Vec3 new_point;
            new_point(0,0) = static_cast<float>(x);
            new_point(1,0) = static_cast<float>(y);
            new_point(2,0) = 1;
            points.push_back(new_point);
            break;
    }

	Color black = {0, 0, 0};

    switch (current_mode)
    {
        case LINE:
            if (points.size() >= 2)
            {
                lines.push_back(new Line(points.front(), points.back(), black));
                points.clear();
            }
            break;
        case CIRCLE:
            if (points.size() >= 2)
            {
				Vec3 distance = points.front() + -1.0f * points.back();
				lines.push_back(new Circle(points.front(), std::sqrt(distance(1,0) * distance(1, 0) + distance(0, 0) * distance(0, 0)), black));
                points.clear();
            }
            break;
        case ELLIPSE:
            if (points.size() >= 3)
            {
                // First click is center, second is x-radius, third is y-radius.
				Vec3 first, second, third;

				first = points.front();
				points.pop_front();
				second = points.front();
				points.pop_front();
				third = points.front();
				points.pop_front();

				Vec3 radius_a, radius_b;
				radius_a = second + -1.0f * first;
				radius_b = third + -1.0f * first;

				lines.push_back(new Ellipse(first, std::sqrt(radius_a(0, 0) * radius_a (0, 0) + radius_a(1, 0) * radius_a(1,0)),
					std::sqrt(radius_b(0, 0) * radius_b (0, 0) + radius_b(1, 0) * radius_b(1,0)), black));
                points.clear();
            }
            break;
        case TRIANGLE:
            if (points.size() >= 3)
            {
                Vec3 first, second, third;
                first = points.front();
                points.pop_front();
                second = points.front();
                points.pop_front();
                third = points.front();
                points.pop_front();

                lines.push_back(new Triangle(first, second, third));
                points.clear();
            }
            break;
    }

    // myCalculateCameraToViewport();
}

void Assignment::clearDrawables()
{
    for (unsigned i = 0; i < lines.size(); ++i)
    {
        delete lines[i];
    }

    lines.clear();
}

void Assignment::myCalculateCameraToViewport()
{

    myCameraToViewport = translate(static_cast<float>(WIDTH) / 2, static_cast<float>(HEIGHT) / 2)
        * scale(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)) * myCam.getCameraTransform();
}

