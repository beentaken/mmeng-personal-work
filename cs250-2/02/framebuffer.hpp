#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <gdiplus.h>

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

class FrameBuffer
{
	public:
		FrameBuffer(unsigned width = 800, unsigned height = 400);
		~FrameBuffer();
		
		void setPixel(int x, int y, float z, const Color& color);
		void clear();
		
		void present(HDC hdc);
		
	private:
		ULONG_PTR gdiplusToken;
		Color* myBuffer;
		unsigned myWidth, myHeight;
};

#endif // FRAMEBUFFER_H
