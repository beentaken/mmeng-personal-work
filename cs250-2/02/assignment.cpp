#include "assignment.hpp"

#include <cmath>
#include <random>

#define SHOW_FPS

#ifdef SHOW_FPS
#include <sstream>
#include <iomanip>
#endif

#include "cs250transform.h"

#include "line.hpp"

namespace
{
    const float PI = 3.1415f;
}

const char *Demo::NAME = "GDI Renderer";

HWND Demo::Window(void) const
{
    return window;
}

Demo::Demo(HINSTANCE hinst, int show)
    : instance(hinst), back_buffer(0), current_time(0), fps_time(0),
      fps_count(0), project_perspective(true)
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

    myCubeEdgeList.push_back(Edge(0, 1));
    myCubeEdgeList.push_back(Edge(0, 2));
    myCubeEdgeList.push_back(Edge(0, 4));
    myCubeEdgeList.push_back(Edge(1, 3));
    myCubeEdgeList.push_back(Edge(1, 5));
    myCubeEdgeList.push_back(Edge(2, 3));
    myCubeEdgeList.push_back(Edge(2, 6));
    myCubeEdgeList.push_back(Edge(3, 7));
    myCubeEdgeList.push_back(Edge(4, 5));
    myCubeEdgeList.push_back(Edge(4, 6));
    myCubeEdgeList.push_back(Edge(5, 7));
    myCubeEdgeList.push_back(Edge(6, 7));

    myFramebuffer = new FrameBuffer(width, width);
}
	

Demo::~Demo(void)
{
	delete myFramebuffer;
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
#if 0
    Graphics graphics(wdc);
    Bitmap bb(width, height, &graphics);
    Graphics backbuffer(&bb);

    SolidBrush background_brush(GdiPlusColor(255, 255, 255, 255));
    backbuffer.FillRectangle(&background_brush, 0, 0, width, height);
#endif
	myFramebuffer->clear();
    // Transform a cube!
    VertexList to_draw;

    Vector position;
    Vector alpha(10, 5, 3);
    Vector beta(1, 5, 1);
    float omega = current_time * 2 * PI / 5;

#if 0
    position.x = std::sin(alpha.x * omega + beta.x);
    position.y = std::sin(alpha.y * omega + beta.y);
    position.z = std::sin(alpha.z * omega + beta.z) - 1;
#else
    position.z = -1;
#endif

    static std::default_random_engine gen(timeGetTime());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    static Vector rot_axis(dist(gen), dist(gen), dist(gen));
    Transform rotation = Rot(rot_axis, omega);

    //for (auto point : myCubeVertices)
    for(auto it = myCubeVertices.begin(); it != myCubeVertices.end(); ++it)
    {
        auto point = *it;
        point = rotation * point;
        if (project_perspective)
            point = PersProj(point + position); // Relocate.
        else
            point = OrthProj(point + position);
        
        // Resize to make it more visible.
        point = width/10 * point;

        // Relocate to center of viewport.
        point.x += width / 2;
        point.y += height / 2;

        to_draw.push_back(point);
    }
    
    drawWireframe(myFramebuffer, to_draw, myCubeEdgeList);

    //graphics.DrawImage(&bb, 0, 0, width, height);
#if 0
	myFramebuffer->clear();
	::Color prok = {0, 0, 0, 255};
	for (int i = 0; i < width; ++i)
	{
		myFramebuffer->setPixel(i, 200, 0.0f, prok);
	}
	
	RenderLine(myFramebuffer, ::Point(0, 0, 0), ::Point(100, 100, 0), prok, prok);
#endif
	myFramebuffer->present(wdc);

    ReleaseDC(window, wdc);
}

void Demo::ToggleProjectionMode(void)
{
    project_perspective = !project_perspective;
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
      if (wp == 'p' || wp == 'P')
        demo->ToggleProjectionMode();
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(wnd,msg,wp,lp);
}

void Demo::drawWireframe(Gdiplus::Graphics& buffer, const VertexList& vertices, const EdgeList& edges)
{
    using namespace Gdiplus;
    Pen pen(Gdiplus::Color(255, 0, 0, 0));
    // Bah, MSVC still doesn't have proper C++11 support...
    // for (auto edge : edges)
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        // Do this because of MSVC, otherwise comment out line if using ranged for.
        auto edge = *it;
        buffer.DrawLine(&pen, vertices[std::get<0>(edge)].x, vertices[std::get<0>(edge)].y,
                vertices[std::get<1>(edge)].x, vertices[std::get<1>(edge)].y);
    }
}

void Demo::drawWireframe(FrameBuffer* fb, const VertexList& vertices, const EdgeList& edges)
{
	Color black = {0, 0, 0, 255};
	
	for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        // Do this because of MSVC, otherwise comment out line if using ranged for.
        auto edge = *it;
        RenderLine(fb, vertices[std::get<0>(edge)], vertices[std::get<1>(edge)], black, black);
    }
}
