#include "render.hpp"

#include <algorithm>

RenderWorld Renderer;

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
}

bool ArrangeTriangle(Triangle& arranged, const Triangle& to_draw)
{
    bool mid_left;

    if (to_draw.p0.y < to_draw.p1.y) // 4, 5, 6
        {
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
                arranged.p0 = to_draw.p0;
                arranged.c0 = to_draw.c0;
				arranged.t0 = to_draw.t1;

                if (to_draw.p1.y < to_draw.p2.y) // 5
                {
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
            if (to_draw.p2.y < to_draw.p1.y) // 2
            {
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
                arranged.p0 = to_draw.p1;
                arranged.c0 = to_draw.c1;
				arranged.t0 = to_draw.t2;

                if (to_draw.p0.y < to_draw.p2.y) // 3
                {
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

void RenderTriangle(const Triangle& to_draw, const std::vector<unsigned char> &texture, int tex_height, int tex_width, int bpp, TextureMode mode)
{
    Triangle arranged;
    
    bool mid_left = ArrangeTriangle(arranged, to_draw);

    Vector4 top;
    Vector4 mid;
    Vector4 low;

    top.x = arranged.p0.x;
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

    if (mid_left)
    {
        slope_left = (mid.x - top.x)/(mid.y - top.y);
        slope_right = (low.x - top.x)/(low.y - top.y);

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
            slope_left = (low.x - top.x)/(low.y - top.y);
            slope_right = (mid.x - top.x)/(mid.y - top.y);

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

		//std::cerr << "Left DUV: " << duv_left << " Right DUV: " << duv_right << std::endl;

		while (current_y < std::ceil(mid.y))
        {
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
        }

        if (mid_left)
        {
            slope_left = (low.x - mid.x)/(low.y - mid.y);
            dc_left.r = static_cast<float>(c2.r - c1.r) / (low.y - mid.y);
            dc_left.g = static_cast<float>(c2.g - c1.g) / (low.y - mid.y);
            dc_left.b = static_cast<float>(c2.b - c1.b) / (low.y - mid.y);

			duv_left = 1.0f / (low.y - mid.y) * (uv2 + -1 * uv1);
        }
        else
        {
            slope_right = (low.x - mid.x)/(low.y - mid.y);
            dc_right.r = static_cast<float>(c2.r - c1.r) / (low.y - mid.y);
            dc_right.g = static_cast<float>(c2.g - c1.g) / (low.y - mid.y);
            dc_right.b = static_cast<float>(c2.b - c1.b) / (low.y - mid.y);

			duv_right = 1.0f / (low.y - mid.y) * (uv2 + -1 * uv1);
        }

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
                //FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
				Vector4 to_set = {255, 255, 255};
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
    }
}

void RenderWorld::addDrawable(const Triangle& new_triangle)
{
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

