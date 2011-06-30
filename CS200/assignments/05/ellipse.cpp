/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: ellipse.cpp
Purpose: Prototypes for an ellipse.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#include "ellipse.hpp"
#include "Utilities.h"

namespace
{
	inline void drawFourWay(int center_x, int center_y, int current_x, int current_y, const Color& color)
	{
		FrameBuffer::SetPixel(center_x + current_x, center_y + current_y, color.r, color.g, color.b);
		FrameBuffer::SetPixel(center_x - current_x, center_y + current_y, color.r, color.g, color.b);
		FrameBuffer::SetPixel(center_x + current_x, center_y - current_y, color.r, color.g, color.b);
		FrameBuffer::SetPixel(center_x - current_x, center_y - current_y, color.r, color.g, color.b);
	}

    void drawEllipse(int center_x, int center_y, int a, int b, Color& color)
    {
        int current_x = 0, current_y = b;

        //int dp = b*b - a*a*b + a*a/4;
		int dp = 4*(b*b - a*a*b + a*a);
        int dE = 4*3*b*b;
        int dSE = 4*(3*b*b - 2*a*a*current_y + 2*a*a);

        int dEE = 4*2*b*b;
        int dESE = 4*2*b*b;
        int dSEE = 4*2*b*b;
        int dSESE = 4*(2*b*b + 2*a*a);

		int phase_change_x = 0;
		int phase_change_y = 2*a*a*b;

		int phase_x_change = 2*b*b;
		int phase_y_change = 2*a*a;

		drawFourWay(center_x, center_y, current_x, current_y, color);

		// ( -2b^2 * x ) / (2a^2 * y) > -1
        while (phase_change_x <= phase_change_y) // Iterate along x-portion
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
				phase_change_y -= phase_y_change;
            }

            ++current_x;
			phase_change_x += phase_x_change;

			drawFourWay(center_x, center_y, current_x, current_y, color);
        }
		//dp = b*b*(current_x-1) - 2*a*a*(current_y-1) + a*a + b*b/4;
		dp = 4*(b*b*(current_x-1) - 2*a*a*(current_y-1) + a*a + b*b);
		dSE = 4*(2*b*b*(current_x-1) + 2*b*b -2*a*a*(current_y-1) + 3*a*a);
		int dS = 4*(-2*a*a*(current_y-1) + 3*a*a);

		int dSS = 4*2*a*a;
		int dSSE = 4*2*a*a;

		int dSES = 4*2*a*a;
		dSESE = 4*2*b*b + 2*a*a;

		while (current_y > 0) // Iterate along y-portion
        {

            if (dp < 0) // SE next;
            {
				dp += dSE;

				dS += dSES;
				dSE += dSESE;

				++current_x;
            }
            else // S next
            {
				dp += dS;

				dS += dSS;
				dSE += dSSE;
            }

			--current_y;
			drawFourWay(center_x, center_y, current_x, current_y, color);
        }

		// Catch the horizontal/vertical edges.
		drawFourWay(center_x, center_y, current_x, current_y, color);
    }
}

Ellipse::Ellipse(Vec3 newcenter, int newradius_a, int newradius_b, Color newcolor)
:center(newcenter), radius_a(newradius_a), radius_b(newradius_b), color(newcolor)
{
}

void Ellipse::draw(const Matrix<3, 3, float>& toViewport)
{
    Vec3 screen_center(toViewport * center);

    drawEllipse(static_cast<int>(screen_center(0, 0)), static_cast<int>(screen_center(1, 0)), radius_a, radius_b, color);
}

