#include "box.hpp"

#include "Matrix4.h"
#include "Point4.h"

#include "render.hpp"

#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

#include "transformations.hpp"

using mat4::scale;
using mat4::rotate;
using mat4::rotate_x;
using mat4::rotate_y;
using mat4::rotate_z;
using mat4::translate;

namespace
{
    void TransformAndDraw(Triangle to_draw, Matrix4 transformation)
    {
        to_draw.p0 = transformation * to_draw.p0;
        to_draw.p1 = transformation * to_draw.p1;
        to_draw.p2 = transformation * to_draw.p2;

		//std::cout << "New p0: " << to_draw.p0 << " p1: " << to_draw.p1 << " p2: " << to_draw.p2 << std::endl;
        Renderer.addDrawable(to_draw);
    }
}

BoxGeometryComponent::BoxGeometryComponent(const std::vector<Triangle> &triangles)
    :myComponents(), myTriangles(triangles), myScale(), myRotation(), myTranslation(), myTurn()
{
}

void BoxGeometryComponent::draw(Matrix4 transformation)
{
    Point4 rotated_move = rotate(myRotation) * Point4(myMove.x, myMove.y, myMove.z);
	//Matrix4 total_transform = transformation * translate(Vector4(rotated_move.x, rotated_move.y, rotated_move.z)) * rotate(myRotation) * scale(myScale);
	Matrix4 total_transform = transformation * translate(myTranslation) * rotate(myRotation) * scale(myScale);
	Matrix4 transform_noscale = transformation * translate(myTranslation) * rotate(myRotation);
    std::for_each(myTriangles.begin(), myTriangles.end(), std::bind2nd(std::ptr_fun(TransformAndDraw), total_transform));

	// Draw all subcomponents.
    std::for_each(myComponents.begin(), myComponents.end(), [&transform_noscale](std::shared_ptr<BoxGeometryComponent> x){ x->draw(transform_noscale); });
}

BoxGeometryComponent& BoxGeometryComponent::addRotation(float angle_x, float angle_y, float angle_z)
{
    myRotation.x += angle_x;
	myRotation.y += angle_y;
    myRotation.z += angle_z;
    return(*this);
}

BoxGeometryComponent& BoxGeometryComponent::addTranslation(float x, float y, float z)
{
	myTranslation.x += x;
	myTranslation.y += y;
	myTranslation.z += z;

    return(*this);
}

BoxGeometryComponent& BoxGeometryComponent::addScale(float x, float y, float z)
{
	myScale.x += x;
	myScale.y += y;
	myScale.z += z;

    return(*this);
}

BoxGeometryComponent& BoxGeometryComponent::attachComponent(std::shared_ptr<BoxGeometryComponent> component)
{
    myComponents.push_back(component);

    return(*this);
}

BoxGeometryComponent& BoxGeometryComponent::move()
{
	static const Vector4 move_amount(0.0f, 0.0f, 5.0f);

	myTranslation += rotate(myRotation) * move_amount;

    return(*this);
}

BoxGeometryComponent& BoxGeometryComponent::turn(float x, float y, float z)
{
    myTurn.x += x;
    myTurn.y += y;
    myTurn.z += z;

    return(*this);
}

Vector4 BoxGeometryComponent::getPosition() const
{
    return(myTranslation);
}

Vector4 BoxGeometryComponent::getRotation() const
{
    return(myRotation);
}

