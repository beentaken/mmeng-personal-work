#pragma once
#ifndef RENDER_H
#define RENDER_H

#include "triangle.hpp"
#include <vector>
#include <deque>
#include <Matrix4.h>

enum TextureMode
{
    VERTEX,
    DECAL,
    MODULATE,
    REPLACE
};

class RenderWorld
{
    public:
        void addDrawable(Triangle new_triangle);
        void think();
        void setWireframeMode(bool mode);
		void setCameraMatrix(Matrix4 new_camera);
		Matrix4 getCameraMatrix() const;

    private:
        std::deque<Triangle> myDrawList;
        bool myWireframeMode;
		Matrix4 myCamera;
};

void RenderTriangle(const Triangle& to_draw, const std::vector<unsigned char> &texture, int tex_height, int tex_width, int bpp, TextureMode mode = VERTEX);

extern RenderWorld Renderer;

#endif // RENDER_H

