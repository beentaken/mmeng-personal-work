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
		/*std::cout << "Drawing transform w " << to_draw.p0.w << std::endl;
		std::cout << "Drawing transform p0 "
			<< to_draw.p0.x << ' '
			<< to_draw.p0.y << ' '
			<< to_draw.p0.z << ' '
			<< to_draw.p0.w << std::endl;*/
        /*
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				std::cout << transformation.m[i][j] << '\t';
			}
			std::cout << std::endl;
		}
        */
        to_draw.p0 = transformation * to_draw.p0;
        to_draw.p1 = transformation * to_draw.p1;
        to_draw.p2 = transformation * to_draw.p2;

		//to_draw.p0.w = 1.0f;
		//to_draw.p1.w = 1.0f;
		//to_draw.p2.w = 1.0f;

		/*std::cout << "Drawing post transform p0 "
			<< to_draw.p0.x << ' '
			<< to_draw.p0.y << ' '
			<< to_draw.p0.z << ' '
			<< to_draw.p0.w << std::endl;*/

        Renderer.addDrawable(to_draw);
    }
}

BoxGeometryComponent::BoxGeometryComponent(std::vector<Triangle> &triangles)
    :myComponents(), myTriangles(triangles), myScale(), myRotation(), myTranslation()
{
}

void BoxGeometryComponent::draw(Matrix4 transformation)
{
	//std::cout << "Draw on box entered." << std::endl;
	Matrix4 total_transform = transformation * translate(myTranslation) * rotate(myRotation) * translate(myMove) * scale(myScale);
	Matrix4 transform_noscale = transformation * translate(myTranslation) * rotate(myRotation) * translate(myMove);
	//std::cout << "Transforms calculated." << std::endl;
    std::for_each(myTriangles.begin(), myTriangles.end(), std::bind2nd(std::ptr_fun(TransformAndDraw), total_transform));
	//std::cout << "Triangles drawn." << std::endl;

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

BoxGeometryComponent& BoxGeometryComponent::move(float x, float y, float z)
{
    myMove.x += x;
    myMove.y += y;
    myMove.z += z;

    return(*this);
}

