#include "draw.hpp"

#include "gdiplus.h"

DrawFun::DrawFun(HDC &context, HBITMAP &buffer)
    :myContext(context), myBuffer(buffer)
{
}

void DrawFun::drawEdges(const VertexList &vertex_list, const EdgeList& edge_list)
{
    using namespace Gdiplus;

    Gdiplus::Pen pen(Color(255,255,255), 1.0f);
    Graphics graphics(myContext);

    for (auto it = edge_list.begin(); it != edge_list.end(); ++it)
    {
        graphics.DrawLine(&pen, vertex_list[std::get<0>(*it)].x, vertex_list[std::get<0>(*it)].y,
                vertex_list[std::get<1>(*it)].x, vertex_list[std::get<1>(*it)].y);
    }
}

