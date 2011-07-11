/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: triangle.cpp
Purpose: Implementation for a triangle.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_5
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#include "triangle.hpp"

#include "Utilities.h"

#include <cmath>

namespace
{
    struct FloatColor
    {
        float r;
        float g;
        float b;
    };
    void drawTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2)
    {
        const FloatColor red = {255, 0, 0};
        const FloatColor green = {0, 255, 0};
        const FloatColor blue = {0, 0, 255};
        FloatColor c0, c1, c2;
        Vec3 top, mid, low;
        bool mid_left;

        if (p0(1, 0) < p1(1, 0)) // 4, 5, 6
        {
            if (p2(1, 0) < p0(1, 0)) // 4
            {
                top = p2;
                mid = p0;
                low = p1;

                c0 = blue;
                c1 = red;
                c2 = green;

                mid_left = true;
            }
            else // 5, 6
            {
                top = p0;
                c0 = red;

                if (p1(1, 0) < p2(1, 0)) // 5
                {
                    mid = p1;
                    low = p2;

                    c1 = green;
                    c2 = blue;

                    mid_left = true;
                }
                else // 6
                {
                    mid = p2;
                    low = p1;

                    c1 = blue;
                    c2 = green;

                    mid_left = false;
                }
            }
        }
        else // 1, 2, 3
        {
            if (p2(1, 0) < p1(1, 0)) // 2
            {
                top = p2;
                mid = p1;
                low = p0;

                c0 = blue;
                c1 = green;
                c2 = red;

                mid_left = false;
            }
            else // 1, 3
            {
                top = p1;
                c0 = green;

                if (p0(1, 0) < p2(1, 0)) // 3
                {
                    mid = p0;
                    low = p2;

                    c1 = red;
                    c2 = blue;

                    mid_left = false;
                }
                else // 1
                {
                    mid = p2;
                    low = p0;

                    c1 = blue;
                    c2 = red;

                    mid_left = true;
                }
            }
        }

        //std::cerr << "Drawing triangle " << top << ' ' << mid << ' ' << low << std::endl;


        // Time to start drawing...
        float current_y = std::ceil(top(1, 0));
        float x_left, x_right;
        x_left = x_right = top(0, 0);

        FloatColor color_left, color_right;
        FloatColor dc_left, dc_right;
        color_left = color_right = c0;

        // Calculate slopes.
        float slope_left, slope_right;

        if (mid_left)
        {
            slope_left = (mid(0, 0) - top(0, 0))/(mid(1, 0) - top(1, 0));
            slope_right = (low(0, 0) - top(0, 0))/(low(1, 0) - top(1, 0));

            dc_left.r = static_cast<float>(c1.r - c0.r) / (mid(1, 0) - top(1, 0));
            dc_left.g = static_cast<float>(c1.g - c0.g) / (mid(1, 0) - top(1, 0));
            dc_left.b = static_cast<float>(c1.b - c0.b) / (mid(1, 0) - top(1, 0));

            dc_right.r = static_cast<float>(c2.r - c0.r) / (low(1, 0) - top(1, 0));
            dc_right.g = static_cast<float>(c2.g - c0.g) / (low(1, 0) - top(1, 0));
            dc_right.b = static_cast<float>(c2.b - c0.b) / (low(1, 0) - top(1, 0));
        }
        else
        {
            slope_left = (low(0, 0) - top(0, 0))/(low(1, 0) - top(1, 0));
            slope_right = (mid(0, 0) - top(0, 0))/(mid(1, 0) - top(1, 0));

            dc_right.r = static_cast<float>(c1.r - c0.r) / (mid(1, 0) - top(1, 0));
            dc_right.g = static_cast<float>(c1.g - c0.g) / (mid(1, 0) - top(1, 0));
            dc_right.b = static_cast<float>(c1.b - c0.b) / (mid(1, 0) - top(1, 0));

            dc_left.r = static_cast<float>(c2.r - c0.r) / (low(1, 0) - top(1, 0));
            dc_left.g = static_cast<float>(c2.g - c0.g) / (low(1, 0) - top(1, 0));
            dc_left.b = static_cast<float>(c2.b - c0.b) / (low(1, 0) - top(1, 0));
        }

        x_left += slope_left * (current_y - top(1, 0));
        x_right += slope_right * (current_y - top(1, 0));

        while (current_y < mid(1, 0))
        {
            FloatColor temp = color_left;
            float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
            float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
            float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

            for (int i = std::ceil(x_left); i < std::ceil(x_right); ++i)
            {
                FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
                temp.r += dr;
                temp.g += dg;
                temp.b += db;
            }

            color_left.r += dc_left.r;
            color_left.g += dc_left.g;
            color_left.b += dc_left.b;

            color_right.r += dc_right.r;
            color_right.g += dc_right.g;
            color_right.b += dc_right.b;

            x_left += slope_left;
            x_right += slope_right;
            ++current_y;
        }

        if (mid_left)
        {
            slope_left = (low(0, 0) - mid(0, 0))/(low(1, 0) - mid(1, 0));
            dc_left.r = static_cast<float>(c2.r - c0.r) / (low(1, 0) - mid(1, 0));
            dc_left.g = static_cast<float>(c2.g - c0.g) / (low(1, 0) - mid(1, 0));
            dc_left.b = static_cast<float>(c2.b - c0.b) / (low(1, 0) - mid(1, 0));
        }
        else
        {
            slope_right = (low(0, 0) - mid(0, 0))/(low(1, 0) - mid(1, 0));
            dc_right.r = static_cast<float>(c2.r - c0.r) / (low(1, 0) - mid(1, 0));
            dc_right.g = static_cast<float>(c2.g - c0.g) / (low(1, 0) - mid(1, 0));
            dc_right.b = static_cast<float>(c2.b - c0.b) / (low(1, 0) - mid(1, 0));
        }

        while (current_y < low(1, 0))
        {
            FloatColor temp = color_left;
            float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
            float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
            float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

            for (int i = std::ceil(x_left); i < std::ceil(x_right); ++i)
            {
                FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
                temp.r += dr;
                temp.g += dg;
                temp.b += db;
            }

            color_left.r += dc_left.r;
            color_left.g += dc_left.g;
            color_left.b += dc_left.b;

            color_right.r += dc_right.r;
            color_right.g += dc_right.g;
            color_right.b += dc_right.b;

            x_left += slope_left;
            x_right += slope_right;
            ++current_y;
        }
    }
}

Triangle::Triangle(const Vec3& point1, const Vec3& point2, const Vec3& point3)
:p0(point1), p1(point2), p2(point3)
{
    //std::cerr << "Created triangle at " << p0 << ' ' << p1 << ' ' << p2 << std::endl;
}

void Triangle::draw(const Mat3& toViewport)
{
	drawTriangle(toViewport * p0, toViewport * p1, toViewport * p2);
}

