#include "geometry.hpp"

#include <algorithm> // for_each

#include "Matrix4.h"

GeometryComponent::GeometryComponent()
    :myComponents()
{
}

void GeometryComponent::draw(Matrix4 transformation)
{
    std::for_each(myComponents.begin(), myComponents.end(), [&transformation](std::shared_ptr<GeometryComponent> x){x->draw(transformation); });
}

