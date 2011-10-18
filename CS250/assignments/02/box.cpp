#include "box.hpp"

#include "Matrix4.h"
#include "Point4.h"

#include "render.hpp"

namespace
{
    void TransformAndDraw(Triangle to_draw, Matrix4 transformation)
    {
        to_draw.p0 = transformation * to_draw.p0;
        to_draw.p1 = transformation * to_draw.p1;
        to_draw.p2 = transformation * to_draw.p2;

        Renderer.addDrawable(to_draw);
    }
}

BoxGeometryComponent::BoxGeometryComponent(std::vector<Triangle> &triangles)
    :GeometryComponent(), myTriangles(triangles), myScale(), myRotation(), myTranslation()
{
}

void BoxGeometryComponent::draw(Matrix4 transformation)
{
    std::for_each(myTriangles.begin(), myTriangles.end(), std::bind2nd(&TransformAndDraw, scale(myScale) * rotate(myRotation) * translate(myTranslation)));
    GeometryComponent::draw(rotate(myRotation) * translate(myTranslation) * transformation);
}

