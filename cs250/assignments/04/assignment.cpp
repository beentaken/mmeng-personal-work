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

#include "camera.hpp"

namespace
{
    float atof(const std::string& input)
    {
        std::stringstream ss(input);

        float to_return;
        ss >> to_return;

        return(to_return);
    }
}

Assignment::Assignment()
    :config("input.txt"), myTank(), offset_size(60.0f), offset_height(30.0f)
{
	config.parse();

    const std::vector<Triangle>& triangles = config.getTriangles();

	// Scatter some boxes.
	boxes.push_back(std::make_shared<BoxGeometryComponent>(triangles));
	boxes.push_back(std::make_shared<BoxGeometryComponent>(triangles));
	boxes.push_back(std::make_shared<BoxGeometryComponent>(triangles));
	boxes.push_back(std::make_shared<BoxGeometryComponent>(triangles));
	boxes.push_back(std::make_shared<BoxGeometryComponent>(triangles));
	boxes.push_back(std::make_shared<BoxGeometryComponent>(triangles));

	boxes[0]->addScale(10, 10, 10).addTranslation(25, 0, -125);
	boxes[1]->addScale(10, 10, 10).addTranslation(25, 0, -100);
	boxes[2]->addScale(10, 10, 10).addTranslation(0, 0, -75);
	boxes[3]->addScale(10, 10, 10).addTranslation(25, 0, -100);
	boxes[4]->addScale(10, 10, 10).addTranslation(0, 0, -125);
	boxes[5]->addScale(10, 10, 10).addTranslation(25, 0, -75);

	myTank["body"] = std::make_shared<BoxGeometryComponent>(triangles);
    /*myTank["turret"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["gun"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel0"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel1"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel2"] = std::make_shared<BoxGeometryComponent>(triangles);
    myTank["wheel3"] = std::make_shared<BoxGeometryComponent>(triangles);*/

    myTank["body"]->addScale(30, 25, 80).addTranslation(0, 0, -100);
    /*
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

    myTank["turret"]->attachComponent(myTank["gun"]);*/

	std::stringstream atofer(config.getCameraData().at("focal"));
	float focal = atof(config.getCameraData().at("focal"));
    std::cout << "Converted focal: " << focal << std::endl;
    
    float left = atof(config.getCameraData().at("left"));
    std::cout << "Converted left: " << left << std::endl;

    float right = atof(config.getCameraData().at("right"));
    std::cout << "Converted right: " << right << std::endl;

    float top = atof(config.getCameraData().at("top"));
    std::cout << "Converted top: " << top << std::endl;

    float bottom = atof(config.getCameraData().at("bottom"));
    std::cout << "Converted bottom: " << bottom << std::endl;

    float near = atof(config.getCameraData().at("near"));
    std::cout << "Converted near: " << near << std::endl;

    float far = atof(config.getCameraData().at("far"));
    std::cout << "Converted far: " << far << std::endl;

	//mvp = mat4::perspective(focal);
	mvp = mat4::perspective(left, right, bottom, top, near, far);
    //Matrix4 mvp;
    //mvp.Identity();
/*
    // Let's get the camera to the center, maybe?
    mvp = mat4::translate(Vector4(static_cast<float>(WIDTH)/2, static_cast<float>(HEIGHT)/2, 0.0f)) // Move to center of screen.
        * mat4::scale(Vector4(WIDTH, HEIGHT, 1.0f, 1.0f)) // Resize to screen.
        * mvp;

    std::cout << "mvp Matrix:" << std::endl << mvp << std::endl;
	*/
}

void Assignment::drawScene()
{
#if 0
    Camera myCamera;
    Vector4 pos = myTank.at("body")->getPosition();
	Vector4 rot = myTank.at("body")->getRotation();

	Vector4 offset = mat4::rotate(rot) * Vector4(0, 0, -offset_size); // Move camera to behind tank direction.
	myCamera.setPosition(pos.x + (offset.x), pos.y + (offset.y) + offset_height, pos.z + (offset.z));
    myCamera.lookAt(pos.x, pos.y, pos.z);

    Matrix4 camera_transform = myCamera.getTransformation();
    //std::cout << "Camera:" << std::endl;
    //std::cout << camera_transform << std::endl;

	Matrix4 my_mvp = mvp; // Stupid MSVC2010 can't capture closures properly.
#endif
	Camera myCamera;
    Vector4 pos = myTank.at("body")->getPosition();
	//Vector4 up = myTank.at("body")->getUpVector();
	Vector4 rot = myTank.at("body")->getRotation();

	Vector4 offset = mat4::rotate(rot) * Vector4(0, 0, -offset_size); // Move camera to behind tank direction.
	Vector4 up = mat4::rotate(rot) * Vector4(0, 1.0f, 0);
	myCamera.setPosition(pos.x + (offset.x), pos.y + (offset.y), pos.z + (offset.z));
    myCamera.lookAt(pos, up);
	std::cout << "Up: " << up.x << ' ' << up.y << ' ' << up.z << std::endl;

	Renderer.setCameraMatrix(myCamera.getTransformation());
	Matrix4 mvp;
	mvp.Identity();
	myTank.at("body")->draw(/* my_mvp * camera_transform */ mvp);
	std::for_each(boxes.begin(), boxes.end(), [/* &my_mvp, &camera_transform */ &mvp](std::shared_ptr<BoxGeometryComponent> x) { x->draw(/*my_mvp * camera_transform */ mvp); });
	Renderer.think();
}

void Assignment::handleInput(int key, int /* x */, int /* y */ )
{
    switch (key)
    {
		case 'w':
			myTank.at("body")->addRotation(-0.2f, 0.0f, 0.0f);
			break;
		case 's':
			myTank.at("body")->addRotation(0.2f, 0.0f, 0.0f);
			break;
		case 'a':
			myTank.at("body")->addRotation(0.0f, 0.0f, 0.2f);
			break;
		case 'd':
			myTank.at("body")->addRotation(0.0f, 0.0f, -0.2f);
			break;
        case 'q':
            myTank.at("body")->addRotation(0.0f, 0.2f, 0.0f);
            break;
        case 'e':
            myTank.at("body")->addRotation(0.0f, -0.2f, 0.0f);
            break;
        case 'r':
            myTank.at("gun")->addRotation(-0.2f, 0.0f, 0.0f);
            break;
        case 'f':
            myTank.at("gun")->addRotation(0.2f, 0.0f, 0.0f);
            break;
        case ' ' :
            myTank.at("body")->move();
			myTank.at("wheel0")->addRotation(0.2f, 0.0f, 0.0f);
			myTank.at("wheel1")->addRotation(0.2f, 0.0f, 0.0f);
			myTank.at("wheel2")->addRotation(0.2f, 0.0f, 0.0f);
			myTank.at("wheel3")->addRotation(0.2f, 0.0f, 0.0f);
            break;
		case 'z':
			offset_size -= 5;
			break;
		case 'x':
			offset_size += 5;
			break;
		case 'h':
			offset_height -= 5;
			break;
		case 'y':
			offset_height += 5;
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

