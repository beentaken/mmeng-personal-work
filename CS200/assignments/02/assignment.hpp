/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment.hpp
Purpose: Prototypes for an assignment class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_2
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef CS200_ASSIGNMENT_H
#define CS200_ASSIGNMENT_H

#include "matrix.hpp" // Mat3
#include <vector>
#include "triangle_model.hpp"
#include "line.hpp"

class Assignment
{
    public:
        Assignment();

        void drawScene();

    private:
        const int num_triangles;
        std::vector<Triangle> triangles;

        std::vector<Line> axis;

        const int camera_width;
        const int camera_height;

        Mat3 myCameraToViewport;

        void myCreateTriangles();
        void myCalculateCameraToViewport();
        void myCreateAxis();
};

#endif // CS200_ASSIGNMENT_H

