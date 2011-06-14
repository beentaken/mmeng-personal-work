/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: camera.hpp
Purpose: Prototypes for a basic camera class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_3
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-04
- End Header --------------------------------------------------------*/

#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.hpp"

class Camera
{
    public:
        Camera(int width, int height);

        void move(int x, int y);
        void turn(float angle);
        void zoom(float scale);

        Mat3 getCameraTransform() const;

    private:
        int pos_x;
        int pos_y;

        float zoomscale;

        float myAngle;

        int myWidth;
        int myHeight;
};

#endif // CAMERA_H

