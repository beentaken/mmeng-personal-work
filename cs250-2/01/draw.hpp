#pragma once
#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <tuple>

#include <windows.h>

#include "cs250vector.h"

class DrawFun
{
    public:
        typedef std::vector<Point> VertexList;
        typedef std::vector<std::tuple<unsigned, unsigned>> EdgeList;

        DrawFun(HDC &context, HBITMAP &buffer);
        void drawEdges(const VertexList& vertex_list, const EdgeList& edge_list);
    private:
        HDC& myContext;
        HBITMAP& myBuffer;
};

#endif // DRAW_H

