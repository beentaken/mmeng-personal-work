#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef WIN32
#include "windows.h"
#endif

#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <cstdio>

#define WIDTH 640
#define HEIGHT 480

#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI / 180.0)

class FrameBuffer
{
	public:
		FrameBuffer();
		~FrameBuffer();

		static void Clear(const unsigned char &r, const unsigned char &g, const unsigned char &b);

		static void Init(const unsigned int &w, const unsigned int &h);
		static void SetPixel(const int &x, const int &y, const unsigned char &r, const unsigned char &g, const unsigned char &b);
		static void GetPixel(const int &x, const int &y, unsigned char &r, unsigned char &g, unsigned char &b);

	public:
		static unsigned char *buffer;
		static int width;
		static int height;
};



// Typedefs for consistency
typedef unsigned char      u8;
typedef char               s8;
typedef unsigned int       u32;
typedef int                s32;
typedef unsigned long      u64;
typedef long               s64;
typedef float              f32;
typedef double             f64;

// Do not change
static const f32 EPSILON = 0.0001f;

#endif // UTILITIES_H

