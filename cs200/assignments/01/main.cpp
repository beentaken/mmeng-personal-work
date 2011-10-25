/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: main.cpp
Purpose: Provided driver file for CS200 assignments.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

#include <cstdlib>
#include "Utilities.h"
#include "line.hpp"
#include "matrix.hpp"
#include "assignment01.hpp"

int winID;

Assignment01 current_assignment;

// If we're not on windows and thus don't have windows.h...
#ifndef WIN32
#define VK_ESCAPE 0x1b
#endif

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case VK_ESCAPE:
			glutDestroyWindow(winID);
			exit(0);
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	}
}

void mouseMove(int x, int y)
{
}

void loop(void)
{
	glutPostRedisplay();
}

void render(void)
{
	FrameBuffer::Clear(255, 255, 255);

	//Put your rendering code here
    current_assignment.drawScene();

	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, FrameBuffer::buffer);
	glutSwapBuffers();
}

void init(void)
{
	FrameBuffer::Init(WIDTH, HEIGHT);

	//Initialize everything here
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	winID = glutCreateWindow("CS200");

	glClearColor(0, 0, 0, 1);

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);
	glutIdleFunc(loop);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	init();

	glutMainLoop();

	delete [] FrameBuffer::buffer;

	return 0;
}
