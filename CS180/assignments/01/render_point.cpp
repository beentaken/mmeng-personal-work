// Marcus Meng
// CS180
// Assignment 01
// Due: Tuesday
// render_point0.cpp
// jsh 1/08

#include "render_point.h"

// Rewrite inside of the loop.

COLORREF render_point(double x, double y, int N)
{
	double a = 0.0, b = 0.0, norm2 = 0.0;
	int n;

	for (n = 0; norm2 < 4.0f && n < N; ++n)
	{
		__asm
		{
			fld b
			fmul st(0), st(0) // b b *; b*b
			fld a
			fmul st(0), st(0) // a a *; a*a, b*b
			fsub st(0), st(1) // -; a*a-b*b, b*b
			fadd x // x +; a*a-b*b + x, b*b

			// double c = a*a - b*b + x evaluated.
			// stack: c, b * b

			fld b // b, c, b*b
			fld a // a, b, c, b*b
			fmul st(0), st(1) // a b *; a*b, b, c, b*b
			fadd st(0), st(0)
			// fscale // 2.0 *; 2*a*b, b, c, b*b
			fadd y // 2*a*b + y, b, c, b*b
			fst b // b, oldb, c, old(b*b)

			// b = 2.0f*a*b +y; evaluated.
			// stack: b,oldb,c, old(b*b)

			fxch st(1) // oldb, b, c, old(b*b)
			fxch st(2) // c, b, oldb, old(b*b)

			// stack: c, b, oldb, old(b*b)

			fst a

			// a = c; evaluated.
			// stack: a, b, oldb, old(b*b)

			fmul st(0), st(0) // a a *; a*a, b, oldb, old(b*b)
			fxch st(1) // b, a*a, oldb, old(b*b)
			fmul st(0), st(0) // b b *; b*b, a*a, oldb, old(b*b)
			fadd st(0), st(1) // +; b*b + a*a, a*a, oldb, old(b*b)
			fst norm2

			// norm2 = a*a + b*b; evaluated.
			// stack: norm2, a*a, oldb, old(b*b)

			// cleanup.
			fstp st(0)
			fstp st(0)
			fstp st(0)
			fstp st(0)
		}
	}

	int value = int(255*(1 - double(n)/N));
	return RGB(value, value, value);
}

// Original function.
#if 0
COLORREF render_point(double x, double y, int N)
{
	double a = 0.0f, b = 0.0f, norm2 = 0.0f;
	int n;

	for (n = 0; norm2 < 4.0f && n < N; ++n)
	{
		double c = a*a - b*b + x; // b b * a a * - x +
		b = 2.0f*a*b + y; // a b * 2.0f * y +
		a = c;
		norm2 = a*a + b*b; a a * b b * +
	}

	int value = int(255*(1 - double(n)/N));
	return RGB(value,value,value);
}

#endif

