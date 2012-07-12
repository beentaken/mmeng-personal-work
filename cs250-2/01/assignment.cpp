#include "assignment.hpp"

#include <cmath>

#define SHOW_FPS

#ifdef SHOW_FPS
#include <sstream>
#include <iomanip>
#endif

const char *Demo::NAME = "GDI Renderer";

HWND Demo::Window(void) const
{
    return window;
}

Demo::Demo(HINSTANCE hinst, int show)
    : instance(hinst), back_buffer(0), current_time(0), fps_time(0),
      fps_count(0), circle_rate(0), circle_fill(true)
{
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = demo_proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(Demo*);
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(0,IDI_APPLICATION);
    wc.hCursor = LoadCursor(0,IDC_ARROW);
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = Demo::NAME;
    RegisterClass(&wc);

    int width = (3*GetSystemMetrics(SM_CYSCREEN))/4;
    RECT rect = {0,0,width,width};
    int style = WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX;
    AdjustWindowRect(&rect,style,FALSE);
    window = CreateWindow(NAME,NAME,style,CW_USEDEFAULT,CW_USEDEFAULT,
             rect.right-rect.left,rect.bottom-rect.top,
             0,0,instance,this);

    circle_rate = 1.0f;
    ShowWindow(window,show);
  
    myCubeVertices.resize(8);
    myCubeVertices[0] = Point( 0.5f,  0.5f,  0.5f);
    myCubeVertices[1] = Point( 0.5f,  0.5f, -0.5f);
    myCubeVertices[2] = Point( 0.5f, -0.5f,  0.5f);
    myCubeVertices[3] = Point( 0.5f, -0.5f, -0.5f);
    myCubeVertices[4] = Point(-0.5f,  0.5f,  0.5f);
    myCubeVertices[5] = Point(-0.5f,  0.5f, -0.5f);
    myCubeVertices[6] = Point(-0.5f, -0.5f,  0.5f);
    myCubeVertices[7] = Point(-0.5f, -0.5f, -0.5f);
}
	

Demo::~Demo(void)
{
    DeleteObject(back_buffer);
    UnregisterClass(NAME,instance);
}


void Demo::Draw(double dt)
{

#ifdef SHOW_FPS
    // update fps display if more than 1/4 second has elapsed
    if (fps_time < 0.25)
    {
        fps_time += dt;  fps_count++;
    }
    else
    {
        std::stringstream ss;
        ss  << std::fixed << std::setprecision(1)
            << Demo::NAME << " (fps: "
            << float(fps_count/fps_time) << ")";
        SetWindowText(window,ss.str().c_str());
        fps_time -= 0.25;  fps_count = 0;
    }
#endif
    // update time elapsed since initialization
    current_time += dt;

    using namespace Gdiplus;
    RECT window_space;
    GetClientRect(window, &window_space);

    int width = window_space.right;
    int height = window_space.bottom;

    HDC wdc = GetDC(window);
    Graphics graphics(wdc);
    Bitmap bb(width, height, &graphics);
    Graphics backbuffer(&bb);

    SolidBrush background_brush(Color(255, 255, 255, 255));
    backbuffer.FillRectangle(&background_brush, 0, 0, width, height);

    Pen      pen(Color(255, 0, 0, 255));
    double angle = circle_rate * current_time;
    int x = int(width * (0.5 + 0.4 * std::cos(angle)));
    int y = int(height * (0.5 + 0.4 * std::sin(angle)));

    SolidBrush circle_brush(Color(100,100,255));
    backbuffer.FillEllipse(&circle_brush, x, y, 20, 20);

    graphics.DrawImage(&bb, 0, 0, width, height);

    ReleaseDC(window, wdc);
}


void Demo::ToggleFillMode(void) {
  circle_fill = !circle_fill;
}


LRESULT CALLBACK Demo::demo_proc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp) {
  static Demo *demo = 0;

  switch (msg) {
    case WM_CREATE: {
      // get the demo class pointer
      demo = reinterpret_cast<Demo*>(
               (reinterpret_cast<CREATESTRUCT*>(lp))->lpCreateParams);
      // create the back buffer
      RECT rect;
      GetClientRect(wnd,&rect);
      HDC dc = GetDC(wnd);
      demo->back_buffer = CreateCompatibleBitmap(dc,rect.right,rect.bottom);
      ReleaseDC(wnd,dc);
      return 0; }
    case WM_CHAR:
      if (wp == 'f' || wp == 'F')
        demo->ToggleFillMode();
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(wnd,msg,wp,lp);
}

