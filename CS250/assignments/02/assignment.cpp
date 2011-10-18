/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: assignment.cpp
Purpose: Implementation for wrapper for first assignment.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_3
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/

#include "assignment.hpp"
#include "Utilities.h"

#include <iostream>

#include "render.hpp"
#include <algorithm>
#include <functional>

namespace
{
	Triangle MakeTriangle(Point4 p0, Point4 p1, Point4 p2)
	{
		Triangle to_return;
		to_return.p0 = p0;
		to_return.p1 = p1;
		to_return.p2 = p2;

		return(to_return);
	}

	void SetTriangleColor(Triangle& tri, float r, float g, float b)
	{
		tri.c0.r = tri.c1.r = tri.c2.r = r;
		tri.c0.g = tri.c1.g = tri.c2.g = g;
		tri.c0.b = tri.c1.b = tri.c2.b = b;
	}

	Matrix4 projection(float focus)
	{
		Matrix4 to_return;

		to_return.m[0][0] = focus;
		to_return.m[1][1] = focus;
		to_return.m[2][2] = focus;

		to_return.m[3][2] = -1;

		return(to_return);
	}
}

Assignment::Assignment()
{
	std::vector<Point4> vertices;
	vertices.push_back(Point4(-0.5, -0.5,  0.5, 1.0));
	vertices.push_back(Point4( 0.5, -0.5,  0.5, 1.0));
	vertices.push_back(Point4( 0.5,  0.5,  0.5, 1.0));
	vertices.push_back(Point4(-0.5,  0.5,  0.5, 1.0));
	vertices.push_back(Point4(-0.5, -0.5, -0.5, 1.0));
	vertices.push_back(Point4( 0.5, -0.5, -0.5, 1.0));
	vertices.push_back(Point4( 0.5,  0.5, -0.5, 1.0));
	vertices.push_back(Point4(-0.5,  0.5, -0.5, 1.0));

	std::vector<Triangle> triangles;
	triangles.push_back(MakeTriangle(vertices[0], vertices[1], vertices[2]));
	triangles.push_back(MakeTriangle(vertices[0], vertices[2], vertices[3]));
	triangles.push_back(MakeTriangle(vertices[1], vertices[5], vertices[6]));
	triangles.push_back(MakeTriangle(vertices[1], vertices[6], vertices[2]));
	triangles.push_back(MakeTriangle(vertices[5], vertices[4], vertices[7]));
	triangles.push_back(MakeTriangle(vertices[5], vertices[7], vertices[6]));
	triangles.push_back(MakeTriangle(vertices[4], vertices[0], vertices[3]));
	triangles.push_back(MakeTriangle(vertices[4], vertices[3], vertices[7]));
	triangles.push_back(MakeTriangle(vertices[3], vertices[2], vertices[6]));
	triangles.push_back(MakeTriangle(vertices[3], vertices[6], vertices[7]));
	triangles.push_back(MakeTriangle(vertices[4], vertices[5], vertices[1]));
	triangles.push_back(MakeTriangle(vertices[4], vertices[1], vertices[0]));

	SetTriangleColor(triangles[0], 0, 0, 0);
	SetTriangleColor(triangles[1], 0, 0, 0);
	SetTriangleColor(triangles[2], 0, 0, 255);
	SetTriangleColor(triangles[3], 0, 0, 255);
	SetTriangleColor(triangles[4], 255, 0, 0);
	SetTriangleColor(triangles[5], 255, 0, 0);
	SetTriangleColor(triangles[6], 0, 255, 0);
	SetTriangleColor(triangles[7], 0, 255, 0);
	SetTriangleColor(triangles[8], 100, 100, 100);
	SetTriangleColor(triangles[9], 100, 100, 100);
	SetTriangleColor(triangles[10], 255, 255, 0);
	SetTriangleColor(triangles[11], 255, 255, 0);

	box = std::make_shared<BoxGeometryComponent>(triangles);
}

void Assignment::drawScene()
{
	Matrix4 mvp = projection(24);

	box->draw(mvp);

	Renderer.think();
}

void Assignment::handleInput(int key, int /* x */, int /* y */ )
{
    switch (key)
    {
		case 'w':
			box->addTranslation(0, 0, -1.0f);
			break;
		case 'a':
			box->addRotation(0.2f);
			break;
        default:
            std::cout << key << " was pressed." << std::endl;
			break;
    }
}

