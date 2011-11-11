/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: Utilities.cpp
Purpose: Provided utilities file for CS200 assignments.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

#include "Utilities.h"
#include <iostream>

namespace
{
    const int bpp = 3; // R, G, B
}

unsigned char *FrameBuffer::buffer = NULL;
int FrameBuffer::width = 0;
int FrameBuffer::height = 0;

float* FrameBuffer::depth_buffer = NULL;

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{
}

//Clears the frame buffer to the given (r, g, b) color
void FrameBuffer::Clear(const unsigned char &r, const unsigned char &g, const unsigned char &b)
{
	for (int i=0; i<width; ++i)
	{
		for (int j=0; j<height; ++j)
		{
			buffer[i * bpp + j * width * bpp] = r;
			buffer[i * bpp + j * width * bpp + 1] = g;
			buffer[i * bpp + j * width * bpp + 2] = b;

			depth_buffer[i + j * width] = 1.0f;
		}
	}
}

//Initializes the frame buffer
void FrameBuffer::Init(const unsigned int &w, const unsigned int &h)
{
	width = w;
	height = h;
	buffer = new unsigned char [width * height * bpp];
	depth_buffer = new float[width * height];

	Clear(255, 255, 255);
}

//Set the pixel's color at (x,y)
void FrameBuffer::SetPixel(const int &x, const int &y, float z, const unsigned char &r, const unsigned char &g, const unsigned char &b)
{
	int _y = height - y;
	//if (z < 0.0f || z > 1.0f ) std::cout << "Depth value: " << z << std::endl;
	if (x < 0 || x >= width || _y < 0 || _y >= height)
		return;
	// Between 0 and 1, and smaller than current value in buffer.
#if 1
	if (z >= 0.0f && z > depth_buffer[x + y * width])
	{
		return;
	}
#endif

	depth_buffer[x + y * width] = z;
	buffer[x * bpp + _y * width * bpp] = r;
	buffer[x * bpp + _y * width * bpp + 1] = g;
	buffer[x * bpp + _y * width * bpp + 2] = b;
}

//Stores the color of the given (x,y) pixel in r, g & b
void FrameBuffer::GetPixel(const int &x, const int &y, unsigned char &r, unsigned char &g, unsigned char &b)
{
	int _y = height - y;

	if (x < 0 || x > width || _y < 0 || _y > height)
		return;

	r = buffer[x * bpp + _y * width * bpp];
	g = buffer[x * bpp + _y * width * bpp + 1];
	b = buffer[x * bpp + _y * width * bpp + 2];
}

/////
