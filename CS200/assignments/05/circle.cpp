/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: circle.cpp
Purpose: Prototypes for a circle.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#include "circle.hpp"

#include "Utilities.h"

namespace
{
    void drawCircle(int center_x, int center_y, int radius, Color& color)
    {
        int current_x = 0, current_y = radius;

        int dp = 5/4 - radius;
        int dE = 2*current_x + 1;
        int dSE = 2 * (current_x - current_y) + 1;

        int dEE = 2;
        int dESE = 2;
        int dSEE = 2;
        int dSESE = 4;

        while (current_x < current_y) // Loooooopy
        {

            if (dp < 0) // E next;
            {
            }
            else // SE next
            {
            }

            FrameBuffer::SetPixel(center_x + current_x, center_y + current_y, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x - current_x, center_y + current_y, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x + current_x, center_y - current_y, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x - current_x, center_y - current_y, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x + current_y, center_y + current_x, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x - current_y, center_y + current_x, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x + current_y, center_y - current_x, color.r, color.g, color.b);
            FrameBuffer::SetPixel(center_x - current_y, center_y - current_x, color.r, color.g, color.b);
        }
    }
}

void Circle::draw(const Matrix<3, 3, float>& toViewport)
{
    Vec3 screen_center(toViewport * center);

    Color black = {0, 0, 0};
    drawCircle(static_cast<int>(screen_center(0, 0)), static_cast<int>(screen_center(1, 0)), radius(0, 0), black);
}

