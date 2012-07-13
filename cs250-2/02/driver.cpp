// win_demo.cpp
// -- minimal win32 demo for real-time animation (cycle hog)
//
// NOTE: this style of win32 program (in particular the greedy message
//   loop in 'WinMain') should only be used for real time animation
//   programs.
//
// CS250 9/02
//
// To compile:
//   cl /EHsc win_demo.cpp user32.lib gdi32.lib


#include <windows.h>
#include "gdiplus.h"

#include "assignment.hpp"

///////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int show) {
    Demo *demo = new Demo(hinst,show);

    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	MSG msg = {0};
    const unsigned framerate = 1000/60; // 60 FPS
    unsigned last_frame_time = timeGetTime();
  
    while (IsWindow(demo->Window()))
    {
        // care and feeding of window
        if (PeekMessage(&msg,demo->Window(),0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // draw and sleep(?)
        unsigned current_frame_time = timeGetTime();

        if (current_frame_time - last_frame_time >= framerate) // Lock to 60 FPS.
        {
            demo->Draw(double(current_frame_time - last_frame_time) / 1000);
            last_frame_time = current_frame_time;
        }
        Sleep(1);
    }

    delete demo;

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}



