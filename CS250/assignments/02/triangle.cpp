/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: triangle.cpp
Purpose: Implementation for a triangle.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_7
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-06-28
- End Header --------------------------------------------------------*/

#include "triangle.hpp"

#include "Utilities.h"

#include <cmath>

namespace
{
	const int tex_height = 128;
	const int tex_width = 128;
	const int bpp = 4;

	int Round(float to_round)
	{
		return static_cast<int>(to_round + 0.5f);
	}

	float Clamp(float to_clamp, float lower, float upper)
	{
		return(std::min(upper, std::max(lower, to_clamp)));
	}

	unsigned char *CreateChessBoardImage()
	{
		unsigned char * chessBoard = (unsigned char *)::operator new(tex_height * tex_width * bpp);
		bool black = false;

		for(int j = 0; j < 128; ++j)
		{
			if(j % 32 == 0)
				black = !black;

			for(int i = 0; i < 128; ++i)
			{
				if(i % 32 == 0)
					black = !black;

				*(chessBoard + (j * tex_width * bpp) + (i * bpp) + 0) = black ? 0 : 255;
				*(chessBoard + (j * tex_width * bpp) + (i * bpp) + 1) = black ? 0 : 255;
				*(chessBoard + (j * tex_width * bpp) + (i * bpp) + 2) = black ? 0 : 255;
				*(chessBoard + (j * tex_width * bpp) + (i * bpp) + 3) = 128;
			}
		}

		return chessBoard;
	}

	void drawTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2, const FloatColor& firstCol, const FloatColor& secondCol, const FloatColor& thirdCol, const Vec3& texCoords0, const Vec3& texCoords1, const Vec3& texCoords2, Triangle::DrawMode mode)
    {
		unsigned char * texture = CreateChessBoardImage();
        FloatColor c0, c1, c2;
        Vec3 top, mid, low;
		Vec3 uv0, uv1, uv2;
        bool mid_left;

        if (p0(1, 0) < p1(1, 0)) // 4, 5, 6
        {
            if (p2(1, 0) < p0(1, 0)) // 4
            {
                top = p2;
                mid = p0;
                low = p1;

                c0 = thirdCol;
                c1 = firstCol;
                c2 = secondCol;

				uv0 = texCoords2;
				uv1 = texCoords0;
				uv2 = texCoords1;

                mid_left = true;
            }
            else // 5, 6
            {
                top = p0;
                c0 = firstCol;
				uv0 = texCoords0;

                if (p1(1, 0) < p2(1, 0)) // 5
                {
                    mid = p1;
                    low = p2;

                    c1 = secondCol;
                    c2 = thirdCol;

					uv1 = texCoords1;
					uv2 = texCoords2;

                    mid_left = true;
                }
                else // 6
                {
                    mid = p2;
                    low = p1;

                    c1 = thirdCol;
                    c2 = secondCol;

					uv1 = texCoords2;
					uv2 = texCoords1;

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

                c0 = thirdCol;
                c1 = secondCol;
                c2 = firstCol;

				uv0 = texCoords2;
				uv1 = texCoords1;
				uv2 = texCoords0;

                mid_left = false;
            }
            else // 1, 3
            {
                top = p1;
                c0 = secondCol;
				uv0 = texCoords1;

                if (p0(1, 0) < p2(1, 0)) // 3
                {
                    mid = p0;
                    low = p2;

                    c1 = firstCol;
                    c2 = thirdCol;

					uv1 = texCoords0;
					uv2 = texCoords2;

                    mid_left = false;
                }
                else // 1
                {
                    mid = p2;
                    low = p0;

                    c1 = thirdCol;
                    c2 = firstCol;

					uv1 = texCoords2;
					uv2 = texCoords0;

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

		Vec3 uv_left, uv_right;
		Vec3 duv_left, duv_right;
		uv_left = uv_right = uv0;

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

			duv_left =  1.0f / (mid(1, 0) - top(1, 0)) * (uv1 + (-1 * uv0));
			duv_right = 1.0f / (low(1, 0) - top(1, 0)) * (uv2 + (-1 * uv0));
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

			duv_left = 1.0f / (low(1, 0) - top(1, 0)) *  (uv2 + (-1 * uv0));
			duv_right = 1.0f / (mid(1, 0) - top(1, 0)) * (uv1 + (-1 * uv0));
        }

        x_left += slope_left * (current_y - top(1, 0));
        x_right += slope_right * (current_y - top(1, 0));

		//std::cerr << "Left DUV: " << duv_left << " Right DUV: " << duv_right << std::endl;

		while (current_y < std::ceil(mid(1, 0)))
        {
            FloatColor temp = color_left;
			float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
            float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
            float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

			Vec3 temp_uv = uv_left;
			Vec3 temp_duv = 1.0f / (x_right - x_left) * (uv_right + -1 * uv_left);

            for (int i = std::ceil(x_left); i <= std::ceil(x_right)-1; ++i)
            {
                //FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
				Color to_set;
				int u = Clamp(Round(temp_uv(0, 0) * tex_width-1), 0, tex_width-1);
				int v = Clamp(Round(temp_uv(1, 0) * tex_height-1), 0, tex_height-1);
				switch (mode)
				{
					case Triangle::VERTEX:
						to_set.r = temp.r;
						to_set.g = temp.g;
						to_set.b = temp.b;
						break;
					case Triangle::DECAL:
						to_set.r = temp.r + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 0] - temp.r);
						to_set.g = temp.g + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 1] - temp.g);
						to_set.b = temp.b + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 2] - temp.b);
						break;
					case Triangle::MODULATE:
						to_set.r = (1.0f / 255.0f * temp.r) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 0]) * 255;
						to_set.g = (1.0f / 255.0f * temp.g) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 1]) * 255;
						to_set.b = (1.0f / 255.0f * temp.b) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 2]) * 255;
						break;
					case Triangle::REPLACE:
						to_set.r = texture[v * tex_height * bpp + u * bpp + 0];
						to_set.g = texture[v * tex_height * bpp + u * bpp + 1];
						to_set.b = texture[v * tex_height * bpp + u * bpp + 2];
						break;
				}

				//std::cerr << "R: " << static_cast<unsigned>(to_set.r) << " G: " << static_cast<unsigned>(to_set.g) << " B: " << static_cast<unsigned>(to_set.b) << std::endl;
				//std::cerr << "U: " << temp_uv(0, 0) << " V: " << temp_uv(1, 0) << std::endl;

				FrameBuffer::SetPixel(i, current_y, to_set.r, to_set.g, to_set.b);
                temp.r += dr;
                temp.g += dg;
                temp.b += db;

				temp_uv += temp_duv;
            }

            color_left.r += dc_left.r;
            color_left.g += dc_left.g;
            color_left.b += dc_left.b;

            color_right.r += dc_right.r;
            color_right.g += dc_right.g;
            color_right.b += dc_right.b;

			uv_left += duv_left;
			uv_right += duv_right;

            x_left += slope_left;
            x_right += slope_right;
            ++current_y;
        }

        if (mid_left)
        {
            slope_left = (low(0, 0) - mid(0, 0))/(low(1, 0) - mid(1, 0));
            dc_left.r = static_cast<float>(c2.r - c1.r) / (low(1, 0) - mid(1, 0));
            dc_left.g = static_cast<float>(c2.g - c1.g) / (low(1, 0) - mid(1, 0));
            dc_left.b = static_cast<float>(c2.b - c1.b) / (low(1, 0) - mid(1, 0));

			duv_left = 1.0f / (low(1, 0) - mid(1, 0)) * (uv2 + -1 * uv1);
        }
        else
        {
            slope_right = (low(0, 0) - mid(0, 0))/(low(1, 0) - mid(1, 0));
            dc_right.r = static_cast<float>(c2.r - c1.r) / (low(1, 0) - mid(1, 0));
            dc_right.g = static_cast<float>(c2.g - c1.g) / (low(1, 0) - mid(1, 0));
            dc_right.b = static_cast<float>(c2.b - c1.b) / (low(1, 0) - mid(1, 0));

			duv_right = 1.0f / (low(1, 0) - mid(1, 0)) * (uv2 + -1 * uv1);
        }

		while (current_y < std::ceil(low(1, 0)))
        {
            FloatColor temp = color_left;
			float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
            float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
            float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

			Vec3 temp_uv = uv_left;
			Vec3 temp_duv = 1.0f / (x_right - x_left) * (uv_right + -1 * uv_left);

            for (int i = std::ceil(x_left); i <= std::ceil(x_right)-1; ++i)
            {
                //FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
				Color to_set = {255, 255, 255};
				int u = Clamp(Round(temp_uv(0, 0) * tex_width-1), 0, tex_width-1);
				int v = Clamp(Round(temp_uv(1, 0) * tex_height-1), 0, tex_height-1);
				switch (mode)
				{
					case Triangle::VERTEX:
						to_set.r = temp.r;
						to_set.g = temp.g;
						to_set.b = temp.b;
						break;
					case Triangle::DECAL:
						to_set.r = temp.r + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 0] - temp.r);
						to_set.g = temp.g + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 1] - temp.g);
						to_set.b = temp.b + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 2] - temp.b);
						break;
					case Triangle::MODULATE:
						to_set.r = (1.0f / 255.0f * temp.r) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 0]) * 255;
						to_set.g = (1.0f / 255.0f * temp.g) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 1]) * 255;
						to_set.b = (1.0f / 255.0f * temp.b) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 2]) * 255;
						break;
					case Triangle::REPLACE:
						to_set.r = texture[v * tex_height * bpp + u * bpp + 0];
						to_set.g = texture[v * tex_height * bpp + u * bpp + 1];
						to_set.b = texture[v * tex_height * bpp + u * bpp + 2];
						break;
				}

				//std::cerr << "R: " << static_cast<unsigned>(to_set.r) << " G: " << static_cast<unsigned>(to_set.g) << " B: " << static_cast<unsigned>(to_set.b) << std::endl;
				//std::cerr << "U: " << temp_uv(0, 0) << " V: " << temp_uv(1, 0) << std::endl;

				FrameBuffer::SetPixel(i, current_y, Clamp(to_set.r, 0, 255), Clamp(to_set.g, 0, 255), Clamp(to_set.b, 0, 255));
                temp.r += dr;
                temp.g += dg;
                temp.b += db;

				temp_uv += temp_duv;
            }

            color_left.r += dc_left.r;
            color_left.g += dc_left.g;
            color_left.b += dc_left.b;

            color_right.r += dc_right.r;
            color_right.g += dc_right.g;
            color_right.b += dc_right.b;

			uv_left += duv_left;
			uv_right += duv_right;

            x_left += slope_left;
            x_right += slope_right;
            ++current_y;
        }

		delete[] texture;
    }
}

Triangle::Triangle(const Vec3& point1, const Vec3& point2, const Vec3& point3, const Color& first, const Color& second, const Color& third, const Vec3& tex0, const Vec3& tex1, const Vec3& tex2)
:p0(point1), p1(point2), p2(point3), c0 (first.r, first.g, first.b), c1 (second.r, second.g, second.b), c2(third.r, third.g, third.b), uv0(tex0), uv1(tex1), uv2(tex2), currentMode(VERTEX)
{
    //std::cerr << "Created triangle at " << p0 << ' ' << p1 << ' ' << p2 << std::endl;
}

void Triangle::draw(const Mat3& toViewport)
{
	drawTriangle(toViewport * p0, toViewport * p1, toViewport * p2, c0, c1, c2, uv0, uv1, uv2, currentMode);
}

void Triangle::setMode(DrawMode to_set)
{
	currentMode = to_set;
}
