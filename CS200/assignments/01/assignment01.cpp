/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment01.cpp
Purpose: Implementation for wrapper for first assignment.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

#include "assignment01.hpp"
#include "Utilities.h"

Assignment01::Assignment01()
    :num_points(9), points(num_points), num_lines(9), lines(num_lines), camera_width(800), camera_height(600)
{
    myCreatePoints();
    myCreateLines();

    myCalculateCameraToViewport();
}

void Assignment01::drawScene()
{
    for (int i = 0; i < num_lines; ++i)
    {
        lines[i].draw(myCameraToViewport);
    }
}

// Sets up the points stated in the assignment.
void Assignment01::myCreatePoints()
{
    int x_list[] = {-300, -300, -100, -100, 300, 300, 100, 100,  100};
    int y_list[] = { 200, -200, -150,  150,   0, 200, 200,   0, -200};

    for (int i = 0; i < num_points; ++i)
    {
        Matrix<3, 3, float> new_point;

        new_point(0,0) = static_cast<float>(x_list[i]);
        new_point(1,1) = static_cast<float>(y_list[i]);
        new_point(2,2) = 1.0f;

        points[i] = new_point ;
    }
}

// To make the point indices match up with the assignment ones.
const Matrix<3, 3, float>& Assignment01::myGetPoint(int point)
{
    return(points[point - 1]);
}

void Assignment01::myCreateLines()
{
    int starts[] = {1, 2, 3, 4, 5, 6, 7, 8, 8};
    int ends[] =   {2, 3, 4, 1, 6, 7, 8, 5, 9};
    
    for (int i = 0; i < num_lines; ++i)
    {
        lines[i] = Line(points[starts[i]-1], points[ends[i] - 1]);
    }
}

void Assignment01::myCalculateCameraToViewport()
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

void Assignment01::test() const
{
    std::cout << "Points vector size: " << points.size() << std::endl;
    for (int i = 0; i < num_points; ++i)
    {
        std::cout << "Point " << i << ": " << points[i](0, 0) << ' ' << points[i](1, 1) << std::endl;
    }
}

