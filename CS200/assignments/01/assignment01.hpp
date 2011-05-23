/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment01.hpp
Purpose: Prototypes for an assignment class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

#ifndef CS200_ASSIGNMENT_01_H
#define CS200_ASSIGNMENT_01_H

#include "matrix.hpp" // Mat3
#include <vector>
#include "line.hpp"

class Assignment01
{
    public:
        Assignment01();

        void drawScene();

    private:
        const int num_points;
        std::vector<Matrix<3, 3, float> > points;

        const int num_lines;
        std::vector<Line> lines;

        Matrix<3, 3, float> myCameraToViewport;

        int camera_width;
        int camera_height;

        void myCreatePoints();
        const Matrix<3, 3, float>& myGetPoint(int point);
        void myCreateLines();

        void myCalculateCameraToViewport();

        void test() const;
};

#endif // CS200_ASSIGNMENT_01_H

