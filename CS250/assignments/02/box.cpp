#include "box.hpp"

#include "Matrix4.h"
#include "Point4.h"

#include "render.hpp"

#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

namespace
{
    void TransformAndDraw(Triangle to_draw, Matrix4 transformation)
    {
        to_draw.p0 = transformation * to_draw.p0;
        to_draw.p1 = transformation * to_draw.p1;
        to_draw.p2 = transformation * to_draw.p2;

        Renderer.addDrawable(to_draw);
    }

	Matrix4 scale(Vector4 scale_factors)
	{
		Matrix4 to_return;
		to_return.m[0][0] = scale_factors.x;
		to_return.m[1][1] = scale_factors.y;
		to_return.m[2][2] = scale_factors.z;
		to_return.m[3][3] = 1;

		return(to_return);
	}

	Matrix4 rotate_x(float angle)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[1][1] = std::cos(angle);
		to_return.m[2][2] = to_return.m[1][1];
		to_return.m[1][2] = -std::sin(angle);
		to_return.m[2][1] = -to_return.m[1][2];

		return(to_return);
	}

	Matrix4 rotate_y(float angle)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[0][0] = std::cos(angle);
		to_return.m[2][2] = to_return.m[0][0];
		to_return.m[0][2] = std::sin(angle);
		to_return.m[2][0] = -to_return.m[0][2];

		return(to_return);
	}

	Matrix4 rotate_z(float angle)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[0][0] = std::cos(angle);
		to_return.m[1][1] = to_return.m[0][0];
		to_return.m[0][1] = -std::sin(angle);
		to_return.m[1][0] = -to_return.m[0][1];

		return(to_return);
	}

	Matrix4 rotate(Vector4 angles)
	{
		return(rotate_x(angles.x) * rotate_y(angles.y) * rotate_z(angles.z));
	}

	Matrix4 translate(Vector4 displacements)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[0][3] = displacements.x;
		to_return.m[1][3] = displacements.y;
		to_return.m[2][3] = displacements.z;

		return(to_return);
	}
}

BoxGeometryComponent::BoxGeometryComponent(std::vector<Triangle> &triangles)
    :myComponents(), myTriangles(triangles), myScale(30, 25, 80), myRotation(), myTranslation(10, 10, -100)
{
}

void BoxGeometryComponent::draw(Matrix4 transformation)
{
	Matrix4 total_transform = scale(myScale) * rotate(myRotation) * translate(myTranslation) * transformation;
    std::for_each(myTriangles.begin(), myTriangles.end(), std::bind2nd(std::ptr_fun(TransformAndDraw), total_transform));
    std::for_each(myComponents.begin(), myComponents.end(), [&myRotation, &myTranslation, &transformation](std::shared_ptr<BoxGeometryComponent> x){ x->draw(rotate(myRotation) * translate(myTranslation) * transformation); });
}

void BoxGeometryComponent::addRotation(float angle)
{
	myRotation.x += angle;
}

void BoxGeometryComponent::addTranslation(float x, float y, float z)
{
	myTranslation.x += x;
	myTranslation.y += y;
	myTranslation.z += z;
}

void BoxGeometryComponent::addScale(float x, float y, float z)
{
	myScale.x += x;
	myScale.y += y;
	myScale.z += z;
}

void BoxGeometryComponent::attachComponent(std::shared_ptr<BoxGeometryComponent> component)
{
    myComponents.push_back(component);
}

