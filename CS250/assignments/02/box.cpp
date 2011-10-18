#include "box.hpp"

#include "Matrix4.h"
#include "Point4.h"

BoxGeometryComponent::BoxGeometryComponent(std::vector<Triangle> &triangles)
    :GeometryComponent(), myTriangles(triangles), myScale(), myRotation(), myTranslation()
{
}

void BoxGeometryComponent::draw(Matrix4 transformation)
{
    // TODO: Calculate transforms, multiply, add box to draw list.
    GeometryComponent::draw(transformation);
}

