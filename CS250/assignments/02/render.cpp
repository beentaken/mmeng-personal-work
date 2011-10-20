// test

#include "render.hpp"

#include <algorithm>
#include <iostream>
#include "Utilities.h"

RenderWorld Renderer;

#ifdef WIN32
#undef min
#undef max
#endif // WIN32

namespace
{
    int Round(float to_round)
	{
		return static_cast<int>(to_round + 0.5f);
	}

	float Clamp(float to_clamp, float lower, float upper)
	{
		return(std::min(upper, std::max(lower, to_clamp)));
	}

	Point4 RenormalizeW(Point4 point)
	{
		point.x /= point.w;
		point.y /= point.w;
		point.z /= point.w;
		point.w /= point.w;

		return(point);
	}

	float fequal(float a, float b)
	{
		return (std::fabs(a - b) < EPSILON);
	}

    float safe_divide(float a, float b)
    {
        if (fequal(b, 0.0f))
        {
            return(0.0f);
        }

        return(a / b);
    }
}
#if 0
bool ArrangeTriangle(Triangle& arranged, const Triangle& to_draw)
{
    bool mid_left;

    if (to_draw.p0.y <= to_draw.p1.y) // 4, 5, 6
    {
        std::cout << "4, 5, 6" << std::endl;
        if (to_draw.p2.y < to_draw.p0.y) // 4
        {
            arranged.p0 = to_draw.p2;
            arranged.p1 = to_draw.p0;
            arranged.p2 = to_draw.p1;

            arranged.c0 = to_draw.c2;
            arranged.c1 = to_draw.c0;
            arranged.c2 = to_draw.c1;

	    	arranged.t0 = to_draw.t2;
		    arranged.t1 = to_draw.t1;
			arranged.t2 = to_draw.t2;

            mid_left = true;
        }
        else // 5, 6
        {
            std::cout << "5, 6" << std::endl;
            arranged.p0 = to_draw.p0;
            arranged.c0 = to_draw.c0;
		    arranged.t0 = to_draw.t1;

            if (to_draw.p1.y < to_draw.p2.y) // 5
            {
                std::cout << "5" << std::endl;
                arranged.p1 = to_draw.p1;
                arranged.p2 = to_draw.p2;

                arranged.c1 = to_draw.c1;
                arranged.c2 = to_draw.c2;

			    arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t2;

                mid_left = true;
            }
            else // 6
            {
                arranged.p1 = to_draw.p2;
                arranged.p2 = to_draw.p1;

                arranged.c1 = to_draw.c2;
                arranged.c2 = to_draw.c1;

			    arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t2;

                mid_left = false;
            }
        }
    }
    else // 1, 2, 3
    {
        std::cout << "1, 2, 3" << std::endl;
        if (to_draw.p2.y < to_draw.p1.y) // 2
        {
            std::cout << "2" << std::endl;
            arranged.p0 = to_draw.p2;
            arranged.p1 = to_draw.p1;
            arranged.p2 = to_draw.p0;

            arranged.c0 = to_draw.c2;
            arranged.c1 = to_draw.c1;
            arranged.c2 = to_draw.c0;

			arranged.t0 = to_draw.t2;
			arranged.t1 = to_draw.t2;
			arranged.t2 = to_draw.t1;

            mid_left = false;
        }
        else // 1, 3
        {
            std::cout << "1, 3" << std::endl;
            arranged.p0 = to_draw.p1;
            arranged.c0 = to_draw.c1;
		    arranged.t0 = to_draw.t2;

            if (to_draw.p0.y < to_draw.p2.y) // 3
            {
                std::cout << "3" << std::endl;
                arranged.p1 = to_draw.p0;
                arranged.p2 = to_draw.p2;

                arranged.c1 = to_draw.c0;
                arranged.c2 = to_draw.c2;

				arranged.t1 = to_draw.t1;
				arranged.t2 = to_draw.t2;

                mid_left = false;
            }
            else // 1
            {
                arranged.p1 = to_draw.p2;
                arranged.p2 = to_draw.p0;

                arranged.c1 = to_draw.c2;
                arranged.c2 = to_draw.c0;

				arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t1;

                mid_left = true;
            }
        }
    }

    return(mid_left);
}
#else
bool ArrangeTriangle(Triangle& arranged, const Triangle& to_draw)
{
    bool mid_left;

    if (to_draw.p0.y <= to_draw.p1.y) // 4, 5, 6
    {
        std::cout << "4, 5, 6" << std::endl;
        if (to_draw.p2.y <= to_draw.p0.y) // 4
        {
            arranged.p0 = to_draw.p2;
            arranged.p1 = to_draw.p0;
            arranged.p2 = to_draw.p1;

            arranged.c0 = to_draw.c2;
            arranged.c1 = to_draw.c0;
            arranged.c2 = to_draw.c1;

	    	arranged.t0 = to_draw.t2;
		    arranged.t1 = to_draw.t0;
			arranged.t2 = to_draw.t1;

            mid_left = false;
        }
        else // 5, 6
        {
            std::cout << "5, 6" << std::endl;
            arranged.p0 = to_draw.p0;
            arranged.c0 = to_draw.c0;
		    arranged.t0 = to_draw.t0;

            if (to_draw.p1.y <= to_draw.p2.y) // 5
            {
                std::cout << "5" << std::endl;
                arranged.p1 = to_draw.p1;
                arranged.p2 = to_draw.p2;

                arranged.c1 = to_draw.c1;
                arranged.c2 = to_draw.c2;

			    arranged.t1 = to_draw.t1;
				arranged.t2 = to_draw.t2;

                mid_left = false;
            }
            else // 6
            {
                arranged.p1 = to_draw.p2;
                arranged.p2 = to_draw.p1;

                arranged.c1 = to_draw.c2;
                arranged.c2 = to_draw.c1;

			    arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t1;

                mid_left = true;
            }
        }
    }
    else // 1, 2, 3
    {
        std::cout << "1, 2, 3" << std::endl;
        if (to_draw.p2.y <= to_draw.p1.y) // 2
        {
            std::cout << "2" << std::endl;
            arranged.p0 = to_draw.p2;
            arranged.p1 = to_draw.p1;
            arranged.p2 = to_draw.p0;

            arranged.c0 = to_draw.c2;
            arranged.c1 = to_draw.c1;
            arranged.c2 = to_draw.c0;

			arranged.t0 = to_draw.t2;
			arranged.t1 = to_draw.t1;
			arranged.t2 = to_draw.t1;

            mid_left = true;
        }
        else // 1, 3
        {
            std::cout << "1, 3" << std::endl;
            arranged.p0 = to_draw.p1;
            arranged.c0 = to_draw.c1;
		    arranged.t0 = to_draw.t1;

            if (to_draw.p0.y <= to_draw.p2.y) // 3
            {
                std::cout << "3" << std::endl;
                arranged.p1 = to_draw.p0;
                arranged.p2 = to_draw.p2;

                arranged.c1 = to_draw.c0;
                arranged.c2 = to_draw.c2;

				arranged.t1 = to_draw.t0;
				arranged.t2 = to_draw.t2;

                mid_left = true;
            }
            else // 1
            {
                arranged.p1 = to_draw.p2;
                arranged.p2 = to_draw.p0;

                arranged.c1 = to_draw.c2;
                arranged.c2 = to_draw.c0;

				arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t0;

                mid_left = false;
            }
        }
    }

    std::cout << "Top: " << arranged.p0.x << ' ' << arranged.p0.y << std::endl;
    std::cout << "Mid: " << arranged.p1.x << ' ' << arranged.p1.y << std::endl;
    std::cout << "Low: " << arranged.p2.x << ' ' << arranged.p2.y << std::endl;
    std::cout << "Mid left? " << mid_left << std::endl;

    return(mid_left);
}
#endif

void RenderTriangle(const Triangle& to_draw, const std::vector<unsigned char> &texture, int tex_height, int tex_width, int bpp, TextureMode mode)
{
	//std::cout << "Triangle renderer entered." << std::endl;
    Triangle arranged;
    
    bool mid_left = ArrangeTriangle(arranged, to_draw);

    Vector4 top;
    Vector4 mid;
    Vector4 low;

    top.x = arranged.p0.x;
	//std::cout << "Initial y: " << arranged.p0.y << std::endl;
    top.y = arranged.p0.y;

    mid.x = arranged.p1.x;
    mid.y = arranged.p1.y;

    low.x = arranged.p2.x;
    low.y = arranged.p2.y;

    Vector4 c0 = arranged.c0;
    Vector4 c1 = arranged.c1;
    Vector4 c2 = arranged.c2;

    Vector4 uv0 = arranged.t0;
    Vector4 uv1 = arranged.t1;
    Vector4 uv2 = arranged.t2;

    // Time to start drawing...
	//std::cout << "Initial: " << std::ceil(top.y) << std::endl;
    float current_y = std::ceil(top.y);
    float x_left, x_right;
    x_left = x_right = top.x;

    Vector4 color_left, color_right;
    Vector4 dc_left, dc_right;
    color_left = color_right = c0;

	Vector4 uv_left, uv_right;
	Vector4 duv_left, duv_right;
	uv_left = uv_right = uv0;

    // Calculate slopes.
    float slope_left, slope_right;

	//std::cout << "1 x_right is " << x_right << std::endl;

    if (mid_left)
    {
		if (fequal(mid.y, top.y))
			slope_left = 0.0f;
		else
			slope_left = (mid.x - top.x)/( mid.y - top.y);

		if (fequal(low.y, top.y))
			slope_right = 0.0f;
		else
			slope_right = (low.x - top.x)/( low.y - top.y);

        dc_left.r = static_cast<float>(c1.r - c0.r) / (mid.y - top.y);
        dc_left.g = static_cast<float>(c1.g - c0.g) / (mid.y - top.y);
        dc_left.b = static_cast<float>(c1.b - c0.b) / (mid.y - top.y);

            dc_right.r = static_cast<float>(c2.r - c0.r) / (low.y - top.y);
            dc_right.g = static_cast<float>(c2.g - c0.g) / (low.y - top.y);
            dc_right.b = static_cast<float>(c2.b - c0.b) / (low.y - top.y);

			duv_left =  1.0f / (uv1 + (uv0 * -1) * (mid.y - top.y));
			duv_right = 1.0f / (uv2 + (uv0 * -1) * (low.y - top.y));
        }
        else
        {
			slope_left = safe_divide(low.x - top.x, low.y - top.y);
			slope_right = safe_divide(mid.x - top.x, mid.y - top.y);

            std::cout << "slope_left is " << slope_left << std::endl;
            std::cout << "slope_right is " << slope_right << std::endl;

			//std::cout << "mx tx my ty " << mid.x << ' ' << top.x << ' ' << mid.y << ' ' << top.y << std::endl;
			//std::cout << "1.1 slope_right is " << slope_right << std::endl;
            dc_right.r = static_cast<float>(c1.r - c0.r) / (mid.y - top.y);
            dc_right.g = static_cast<float>(c1.g - c0.g) / (mid.y - top.y);
            dc_right.b = static_cast<float>(c1.b - c0.b) / (mid.y - top.y);

            dc_left.r = static_cast<float>(c2.r - c0.r) / (low.y - top.y);
            dc_left.g = static_cast<float>(c2.g - c0.g) / (low.y - top.y);
            dc_left.b = static_cast<float>(c2.b - c0.b) / (low.y - top.y);

			duv_left = 1.0f / (low.y - top.y) *  (uv2 + (-1 * uv0));
			duv_right = 1.0f / (mid.y - top.y) * (uv1 + (-1 * uv0));
        }

        x_left += slope_left * (current_y - top.y);
        x_right += slope_right * (current_y - top.y);
		//std::cout << "Slope mod is " << slope_right << "*" << (current_y - top.y) << std::endl;
		//std::cout << "2 x_right is " << x_right << std::endl;

		//std::cerr << "Left DUV: " << duv_left << " Right DUV: " << duv_right << std::endl;

		while (current_y < std::ceil(mid.y))
        {
            std::cout << "Entering upper loop." << std::endl;
            Vector4 temp = color_left;
			float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
            float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
            float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

			Vector4 temp_uv = uv_left;
			Vector4 temp_duv = 1.0f / (x_right - x_left) * (uv_right + -1 * uv_left);

            for (int i = std::ceil(x_left); i <= std::ceil(x_right)-1; ++i)
            {
                //FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
				Vector4 to_set;
				int u = Clamp(Round(temp_uv.x * tex_width-1), 0, tex_width-1);
				int v = Clamp(Round(temp_uv.y * tex_height-1), 0, tex_height-1);
				switch (mode)
				{
					case VERTEX:
						to_set.r = temp.r;
						to_set.g = temp.g;
						to_set.b = temp.b;
						break;
					case DECAL:
						to_set.r = temp.r + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 0] - temp.r);
						to_set.g = temp.g + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 1] - temp.g);
						to_set.b = temp.b + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 2] - temp.b);
						break;
					case MODULATE:
						to_set.r = (1.0f / 255.0f * temp.r) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 0]) * 255;
						to_set.g = (1.0f / 255.0f * temp.g) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 1]) * 255;
						to_set.b = (1.0f / 255.0f * temp.b) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 2]) * 255;
						break;
					case REPLACE:
						to_set.r = texture[v * tex_height * bpp + u * bpp + 0];
						to_set.g = texture[v * tex_height * bpp + u * bpp + 1];
						to_set.b = texture[v * tex_height * bpp + u * bpp + 2];
						break;
				}

				//std::cerr << "R: " << static_cast<unsigned>(to_set.r) << " G: " << static_cast<unsigned>(to_set.g) << " B: " << static_cast<unsigned>(to_set.b) << std::endl;
				//std::cerr << "U: " << temp_uv.x << " V: " << temp_uv.y << std::endl;

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

			//std::cout << current_y << " out of " << std::ceil(mid.y) << std::endl;
        }
		//std::cout << "x_right is " << x_right << std::endl;

		//std::cout << "Triangle upper pass complete." << std::endl;
        if (mid_left)
        {
            slope_left = safe_divide(low.x - mid.x, low.y - mid.y);
            dc_left.r = static_cast<float>(c2.r - c1.r) / (low.y - mid.y);
            dc_left.g = static_cast<float>(c2.g - c1.g) / (low.y - mid.y);
            dc_left.b = static_cast<float>(c2.b - c1.b) / (low.y - mid.y);

			duv_left = 1.0f / (low.y - mid.y) * (uv2 + -1 * uv1);
        }
        else
        {
            slope_right = safe_divide(low.x - mid.x, low.y - mid.y);
            std::cout << "New slope_right is " << slope_right << std::endl;
            dc_right.r = static_cast<float>(c2.r - c1.r) / (low.y - mid.y);
            dc_right.g = static_cast<float>(c2.g - c1.g) / (low.y - mid.y);
            dc_right.b = static_cast<float>(c2.b - c1.b) / (low.y - mid.y);

			duv_right = 1.0f / (low.y - mid.y) * (uv2 + -1 * uv1);
        }

		//std::cout << current_y << " out of " << std::ceil(low.y) << std::endl;
		//std::cout << "x_right is " << x_right << std::endl;
        std::cout << "Entering lower loop." << std::endl;
		while (current_y < std::ceil(low.y))
        {
            Vector4 temp = color_left;
			float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
            float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
            float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

			Vector4 temp_uv = uv_left;
			Vector4 temp_duv = 1.0f / (x_right - x_left) * (uv_right + -1 * uv_left);

            for (int i = std::ceil(x_left); i <= std::ceil(x_right)-1; ++i)
            {
				//std::cout << "Lower inner loop entered " << i << "/" << std::ceil(x_right) - 1 << std::endl;
                //FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
				Vector4 to_set;
				to_set.r = to_set.g = to_set.b = 255;
				int u = Clamp(Round(temp_uv.x * tex_width-1), 0, tex_width-1);
				int v = Clamp(Round(temp_uv.y * tex_height-1), 0, tex_height-1);
				switch (mode)
				{
					case VERTEX:
						to_set.r = temp.r;
						to_set.g = temp.g;
						to_set.b = temp.b;
						break;
					case DECAL:
						to_set.r = temp.r + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 0] - temp.r);
						to_set.g = temp.g + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 1] - temp.g);
						to_set.b = temp.b + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 2] - temp.b);
						break;
					case MODULATE:
						to_set.r = (1.0f / 255.0f * temp.r) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 0]) * 255;
						to_set.g = (1.0f / 255.0f * temp.g) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 1]) * 255;
						to_set.b = (1.0f / 255.0f * temp.b) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 2]) * 255;
						break;
					case REPLACE:
						to_set.r = texture[v * tex_height * bpp + u * bpp + 0];
						to_set.g = texture[v * tex_height * bpp + u * bpp + 1];
						to_set.b = texture[v * tex_height * bpp + u * bpp + 2];
						break;
				}

				//std::cerr << "R: " << static_cast<unsigned>(to_set.r) << " G: " << static_cast<unsigned>(to_set.g) << " B: " << static_cast<unsigned>(to_set.b) << std::endl;
				//std::cerr << "U: " << temp_uv.x << " V: " << temp_uv.y << std::endl;

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
		//std::cout << "Triangle lower pass one round. (" << current_y << "/" << std::ceil(low.y) << ")" << std::endl;
    }
		//std::cout << "Triangle rasterizer pass complete." <<  std::endl;
}

void RenderWorld::addDrawable(Triangle new_triangle)
{
	//std::cout << "Prenormalized p0 w " << new_triangle.p0.w << std::endl;
	//std::cout << "Prenormalized p0 y " << new_triangle.p0.y << std::endl;
	new_triangle.p0 = RenormalizeW(new_triangle.p0);
	new_triangle.p1 = RenormalizeW(new_triangle.p1);
	new_triangle.p2 = RenormalizeW(new_triangle.p2);

	//std::cout << "Renormalized p0 y " << new_triangle.p0.y << std::endl;
	//std::cout << "Renormalized p0 w " << new_triangle.p0.w << std::endl;
    myDrawList.push_back(new_triangle);
}

void RenderWorld::think()
{
    std::vector<unsigned char> empty_texture;
    while(!myDrawList.empty())
    {
        RenderTriangle(myDrawList.front(), empty_texture, 0, 0, 0);

        myDrawList.pop_front();
    }
}

