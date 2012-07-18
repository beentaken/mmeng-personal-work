#include "line.hpp"
#include <algorithm>

namespace
{
	template<bool MoreHorizontal>
        void DrawLine(FrameBuffer* fb, Point p0, Point p1, Color c0, Color c1);

    template<>
    void DrawLine<true>(FrameBuffer* fb, Point p0, Point p1, Color c0, Color /* c1 */)
	{
        int y_step = (p1.y < p0.y) ? -1 : 1;

        int current_x = p0.x;
        int current_y = p0.y;

        if (y_step == 1)
            std::swap(p0.y, p1.y);

		int a = p1.y - p0.y;
        int b = p1.x - p0.x;
        // int c = end_x * start_y - end_y * start_x;

        int dp = 2 * a + b;

        int steps = p1.x - p0.x; // Number of iterations.

        // Draw initial pixel.
        fb->setPixel(current_x, current_y, 0.0f, c0);

        while (steps--)
        {
            if (dp < 0)
            {
                current_y += y_step;

                dp += a + b;
            }
            else
            {
                dp += a;
            }

            ++current_x;
            fb->setPixel(current_x, current_y, 0.0f, c0);
        }
	}
	template<>
	void DrawLine<false>(FrameBuffer* fb, Point p0, Point p1, Color c0, Color /* c1 */)
	{
		int x_step = (p1.x < p0.x) ? -1 : 1;

        int current_x = p0.x;
        int current_y = p0.y;

        if (x_step == 1)
            std::swap(p0.x, p1.x);

		int a = p1.x - p0.x;
        int b = p1.y - p0.y;
        // int c = end_y * start_x - end_x * start_y;

        int dp = 2 * a + b;

        int steps = p1.y - p0.y; // Number of iterations.

        // Draw initial pixel.
        fb->setPixel(current_x, current_y, 0.0f, c0);

        while (steps--)
        {
            if (dp < 0)
            {
                current_x += x_step;

                dp += a + b;
            }
            else
            {
                dp += a;
            }

            ++current_y;
            fb->setPixel(current_x, current_y, 0.0f, c0);
        }
    }
}

void RenderLine(FrameBuffer* fb, Point p0, Point p1, Color c0, Color c1)
{
	bool more_horizontal = abs(p1.x - p0.x) > abs(p1.y - p0.y);

	// Make sure the start point is always "lower" on the iterating factor than the end.
	if (more_horizontal)
	{		
		if (p1.x < p0.x) // Bah, wrong order, swap!
		{
			std::swap(p0, p1);
            std::swap(c0, c1);
		}
		
		DrawLine<true>(fb, p0, p1, c0, c1);
	}
	else
	{		
		if (p1.y < p0.y) // Bah, wrong order, swap!
		{
			std::swap(p0, p1);
			std::swap(c0, c1);
		}
		
		DrawLine<false>(fb, p0, p1, c0, c1);
	}
}