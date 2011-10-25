/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment.hpp
Purpose: Prototypes for an assignment class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#ifndef CS200_ASSIGNMENT_H
#define CS200_ASSIGNMENT_H

#include "matrix.hpp" // Mat3
#include <vector>
#include <deque>
#include "camera.hpp"
#include "drawable.hpp"

class Assignment
{
    public:
        Assignment();

        void drawScene();

        void handleInput(int key, int x = 0, int y = 0);

    private:

        enum Mode
        {
            LINE,
            CIRCLE,
            ELLIPSE
        };

        Mode current_mode;
        std::deque<Vec3> points;
        std::vector<Drawable*> lines;

        const int camera_width;
        const int camera_height;

        Mat3 myCameraToViewport;

        Camera myCam;

        void clearDrawables();
        void myCalculateCameraToViewport();
};

#endif // CS200_ASSIGNMENT_H

