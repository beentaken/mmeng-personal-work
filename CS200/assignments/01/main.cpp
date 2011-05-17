#include "Utilities.h"
#include "line.hpp"
#include "matrix.hpp"
#include <iostream>

int winID;

// If we're not on windows and thus don't have windows.h...
#ifndef WIN32
#define VK_ESCAPE 27
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
	Mat3 first_point, second_point;
	
	first_point(0, 0) = 200;
	first_point(1, 1) = 400;
	
	second_point(0, 0) = 20;
	second_point(1, 1) = 50;
	
	Line myLine(first_point, second_point);
	
	myLine.draw();

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
