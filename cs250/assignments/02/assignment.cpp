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

#include "transformations.hpp"
#include <sstream>

#include "parser.hpp"

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
        tri.c0.a = tri.c1.a = tri.c2.a = 255;
	}

	Matrix4 perspective(float focus)
	{
		Matrix4 to_return;
		to_return.Zero();

		to_return.m[0][0] = focus;
		to_return.m[1][1] = -focus;
		to_return.m[2][2] = focus;

		to_return.m[3][2] = -1.0f;

		return(to_return);
	}

    Matrix4 ortho(float focus)
    {
        Matrix4 to_return;
        to_return.Zero();

        to_return.m[0][0] = focus;
        to_return.m[1][1] = -focus;
        to_return.m[3][3] = 1.0f;
        to_return.m[3][2] = -1.0f;

        return(to_return);
    }
}

Assignment::Assignment()
    :config("input.txt"), myTank()
{
	config.parse();

    const std::vector<Triangle>& triangles = config.getTriangles();

	myTank["body"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["turret"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["gun"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel0"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel1"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel2"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel3"] = std::make_shared<BoxGeometryComponent>(triangles);

    myTank["body"]->addScale(30, 25, 80).addTranslation(0, 0, -100);
    myTank["turret"]->addScale(25, 15, 25).addTranslation(0, 20, 0);
    myTank["gun"]->addScale(5, 5, 40).addTranslation(0, 0, 22.5);
    myTank["wheel0"]->addScale(5, 20, 20).addTranslation(17.5, -12.5, -25);
    myTank["wheel1"]->addScale(5, 20, 20).addTranslation(-17.5, -12.5, -25);
    myTank["wheel2"]->addScale(5, 20, 20).addTranslation(17.5, -12.5, 25);
    myTank["wheel3"]->addScale(5, 20, 20).addTranslation(-17.5, -12.5, 25);

    myTank["body"]->attachComponent(myTank["turret"])
                   .attachComponent(myTank["wheel0"])
                   .attachComponent(myTank["wheel1"])
                   .attachComponent(myTank["wheel2"])
                   .attachComponent(myTank["wheel3"]);

    myTank["turret"]->attachComponent(myTank["gun"]);
}

void Assignment::drawScene()
{
	std::stringstream atofer(config.getCameraData().at("focal"));
	float focal;
	atofer >> focal;
	Matrix4 mvp = perspective(focal);
    //Matrix4 mvp;
    //mvp.Identity();

    // Let's get the camera to the center, maybe?
    mvp = mat4::translate(Vector4(static_cast<float>(WIDTH)/2, static_cast<float>(HEIGHT)/2, 0.0f)) * mvp;
#if 1
	myTank.at("body")->draw(mvp);
#else
    const float size = 200.0f;
    Point4 p0(-size, -size, size, 1.0f);
    Point4 p1(size, -size, size, 1.0f);
    Point4 p2(size, size, size, 1.0f);
    Point4 p3(-size, size, size, 1.0f);
    Triangle test1 = MakeTriangle(p0, p1, p2);
    Triangle test2 = MakeTriangle(p0, p2, p3);

    SetTriangleColor(test1, 255, 0, 0);
    SetTriangleColor(test2, 0, 255, 0);

    test1.p0 = mvp * test1.p0;
    test1.p1 = mvp * test1.p1;
    test1.p2 = mvp * test1.p2;

    test2.p0 = mvp * test2.p0;
    test2.p1 = mvp * test2.p1;
    test2.p2 = mvp * test2.p2;

    Renderer.addDrawable(test1);
    Renderer.addDrawable(test2);
#endif
	Renderer.think();
}

void Assignment::handleInput(int key, int /* x */, int /* y */ )
{
    switch (key)
    {
		case 'w':
			myTank.at("body")->addTranslation(0, -20.0f, 0);
			break;
		case 's':
			myTank.at("body")->addTranslation(0, 20.0f, 0);
			break;
		case 'a':
			myTank.at("body")->addRotation(0.0f, 0.2f, 0.0f);
			break;
		case 'd':
			myTank.at("body")->addRotation(0.0f, -0.2f, 0.0f);
			break;
        case 'q':
            myTank.at("turret")->addRotation(0.0f, 0.2f, 0.0f);
            break;
        case 'e':
            myTank.at("turret")->addRotation(0.0f, -0.2f, 0.0f);
            break;
        case 'r':
            myTank.at("gun")->addRotation(-0.2f, 0.0f, 0.0f);
            break;
        case 'f':
            myTank.at("gun")->addRotation(0.2f, 0.0f, 0.0f);
            break;
        case ' ' :
            myTank.at("body")->move(0.0f, 0.0f, 20.0f);
            break;
        case '1':
            Renderer.setWireframeMode(true);
            break;
        case '2':
            Renderer.setWireframeMode(false);
            break;
        default:
            std::cout << key << " was pressed." << std::endl;
			break;
    }
}

