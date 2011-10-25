/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: camera.cpp
Purpose: Implementation for a basic camera class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_3
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-04
- End Header --------------------------------------------------------*/

#include "camera.hpp"

#include "matrix_transform.hpp"

#include <iostream>

Camera::Camera(int width, int height)
    :pos_x(0), pos_y(0), zoomscale(1.0f), myAngle(0.0f), myWidth(width), myHeight(height)
{
    std::cerr << "Camera constructor complete." << std::endl;
}

void Camera::move(int x, int y)
{
    pos_x += x;
    pos_y += y;
}

void Camera::turn(float angle)
{
    myAngle += angle;
}

void Camera::zoom(float scale)
{
    zoomscale *= scale;
}

Mat3 Camera::getCameraTransform() const
{
    //std::cerr << "Retrieving camera transform matrix." << std::endl;
    // Rescale and flip axis.
    Mat3 normalize = mat3t::scale(1.0f / static_cast<float>(myWidth), 1.0f / -static_cast<float>(myHeight));
    Mat3 spin = mat3t::rotate(myAngle);
    Mat3 shift = mat3t::translate(pos_x, pos_y);
    Mat3 current_zoom = mat3t::scale(zoomscale, zoomscale);

    // Turn it, shift it, and then normalize!
    return(normalize * shift * spin * current_zoom);
}

