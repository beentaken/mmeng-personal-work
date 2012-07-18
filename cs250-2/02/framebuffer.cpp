#include "framebuffer.hpp"

#include <cstring> // memset

FrameBuffer::FrameBuffer(unsigned width, unsigned height)
:myBuffer(nullptr), myWidth(width), myHeight(height)
{
	using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	myBuffer = new ::Color[width * height];
}

FrameBuffer::~FrameBuffer()
{
	Gdiplus::GdiplusShutdown(gdiplusToken);
	if (nullptr != myBuffer)
	{
		delete[] myBuffer;
	}
}

// Z is unused, no depth buffering here.
void FrameBuffer::setPixel(int x, int y, float /* z */, const Color& color)
{
	if (x < 0 || x >= myWidth || y < 0 || y > myWidth)
		return;
	myBuffer[y * myWidth + x] = color;
}

void FrameBuffer::clear()
{
	std::memset(myBuffer, 255, sizeof(Color) * myWidth * myHeight);
}

void FrameBuffer::present(HDC hdc)
{
	using namespace Gdiplus;
	BitmapData data;
	data.Width = myWidth;
	data.Height = myHeight;
	data.Stride = sizeof(::Color) * myWidth;
	data.PixelFormat = PixelFormat32bppRGB;
	data.Scan0 = reinterpret_cast<void*>(myBuffer);
	data.Reserved = NULL;
	
	Rect window(0, 0, myWidth, myHeight);
	Graphics graphics(hdc);
	Bitmap backbuffer(myWidth, myHeight, PixelFormat32bppRGB);
	
	backbuffer.LockBits(&window, ImageLockModeWrite|ImageLockModeUserInputBuf, PixelFormat32bppRGB, &data);
	backbuffer.UnlockBits(&data);
	
	graphics.DrawImage(&backbuffer, 0, 0, myWidth, myHeight);
}
