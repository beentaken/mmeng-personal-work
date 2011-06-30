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
	inline void drawEightWay(int center_x, int center_y, int current_x, int current_y, const Color& color)
	{
		FrameBuffer::SetPixel(center_x + current_x, center_y + current_y, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x - current_x, center_y + current_y, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x + current_x, center_y - current_y, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x - current_x, center_y - current_y, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x + current_y, center_y + current_x, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x - current_y, center_y + current_x, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x + current_y, center_y - current_x, color.r, color.g, color.b);
        FrameBuffer::SetPixel(center_x - current_y, center_y - current_x, color.r, color.g, color.b);
	}

    void drawCircle(int center_x, int center_y, int radius, Color& color)
    {
        int current_x = 0, current_y = radius;

        //int dp = 1 - radius; // Approximation of 5/4 - radius.
		int dp = 5 - 4*radius;
        int dE = 4*(2*current_x + 1);
        int dSE = 4*(2 * (current_x - current_y) + 1);

        int dEE = 4*2;
        int dESE = 4*2;
        int dSEE = 4*2;
        int dSESE = 4*4;

        while (current_x < current_y) // Loooooopy
        {

            if (dp < 0) // E next;
            {
				dp += dE;

				dE += dEE;
				dSE += dESE;
            }
            else // SE next
            {
				dp += dSE;

				dE += dSEE;
				dSE += dSESE;

				--current_y;
            }

            drawEightWay(center_x, center_y, current_x, current_y, color);

			++current_x;
        }
    }
}

Circle::Circle(Vec3 newcenter, int newradius, Color newcolor)
:center(newcenter), radius(newradius), color(newcolor)
{
}

void Circle::draw(const Matrix<3, 3, float>& toViewport)
{
    Vec3 screen_center(toViewport * center);

	drawCircle(static_cast<int>(screen_center(0, 0)), static_cast<int>(screen_center(1, 0)), radius, color);
}

