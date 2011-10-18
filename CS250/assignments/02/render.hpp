#pragma once
#ifndef RENDER_H
#define RENDER_H

#include "triangle.hpp"
#include <vector>

enum TextureMode
{
    VERTEX,
    DECAL,
    MODULATE,
    REPLACE
};

void RenderTriangle(const Triangle& to_draw, const std::vector<unsigned char> &texture, int tex_height, int tex_width, int bpp, TextureMode mode = VERTEX);

#endif // RENDER_H

