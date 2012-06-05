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

#include <sstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <array>

#include "cs250vector.h"

class Demo {
  public:
    static const char *NAME;
    Demo(HINSTANCE, int);
    ~Demo(void);
    void Draw(double dtime);
    void ToggleFillMode(void);
    HWND Window(void) const;
  private:
    HINSTANCE instance;
    HWND window;
    HBITMAP back_buffer;
    double current_time, fps_time;
    int fps_count;
    float circle_rate;
    bool circle_fill;
    Demo(const Demo&);
    Demo& operator=(const Demo&);
    static LRESULT CALLBACK demo_proc(HWND, UINT, WPARAM, LPARAM);

    std::array<Point, 8> myCubeVertices;
};




///////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int show) {
  Demo *demo = new Demo(hinst,show);

  MSG msg;
  std::clock_t ticks = std::clock();
  while (IsWindow(demo->Window())) {
    // care and feeding of window
    if (PeekMessage(&msg,demo->Window(),0,0,PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    // draw and sleep(?)
    std::clock_t temp = std::clock();
    //demo->Draw(double(temp - ticks)/double(CLK_TCK));
    demo->Draw(double(temp - ticks)/double(CLOCKS_PER_SEC));
    ticks = temp;
    // you may wish to edit this to improve the frame rate
    Sleep(1);
  }

  delete demo;
  return msg.wParam;
}


///////////////////////////////////////////////////////////////////////
// implementation
///////////////////////////////////////////////////////////////////////


const char *Demo::NAME = "Cycle Hog Demo";


HWND Demo::Window(void) const {
  return window;
}


Demo::Demo(HINSTANCE hinst, int show)
    : instance(hinst), back_buffer(0), current_time(0), fps_time(0),
      fps_count(0), circle_rate(0), circle_fill(true) {

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
  std::srand(unsigned(std::time(0)));
  circle_rate = 2.0f - 4.0f*float(rand())/float(RAND_MAX);
  ShowWindow(window,show);
  
    myCubeVertices[0] = Point( 0.5f,  0.5f,  0.5f);
    myCubeVertices[1] = Point( 0.5f,  0.5f, -0.5f);
    myCubeVertices[2] = Point( 0.5f, -0.5f,  0.5f);
    myCubeVertices[3] = Point( 0.5f, -0.5f, -0.5f);
    myCubeVertices[4] = Point(-0.5f,  0.5f,  0.5f);
    myCubeVertices[5] = Point(-0.5f,  0.5f, -0.5f);
    myCubeVertices[6] = Point(-0.5f, -0.5f,  0.5f);
    myCubeVertices[7] = Point(-0.5f, -0.5f, -0.5f);
}
	

Demo::~Demo(void) {
  DeleteObject(back_buffer);
  UnregisterClass(NAME,instance);
}


void Demo::Draw(double dt) {

  // update fps display if more than 1/4 second has elapsed
  if (fps_time < 0.25) {
    fps_time += dt;  fps_count++; }
  else {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1)
       << Demo::NAME << " (fps: "
       << float(fps_count/fps_time) << ")";
    SetWindowText(window,ss.str().c_str());
    fps_time -= 0.25;  fps_count = 0;
  }
  // update time elapsed since initialization
  current_time += dt;

  // get ready to draw to back buffer
  HDC wdc = GetDC(window);
  HDC bdc = CreateCompatibleDC(wdc);
  RECT rect;
  GetClientRect(window,&rect);
  SelectObject(bdc,back_buffer);
  int width = rect.right,
      height = rect.bottom;

//////////////////////////////////////
// *** drawing code starts here *** //
//////////////////////////////////////
  HPEN blue_pen = CreatePen(PS_SOLID,2,RGB(100,100,255));
  double angle = circle_rate*current_time;
  int x = int(width*(0.5 + 0.4*std::cos(angle))),
      y = int(height*(0.5 + 0.4*std::sin(angle)));

  // draw to back buffer
  FillRect(bdc,&rect,HBRUSH(GetStockObject(WHITE_BRUSH)));
  HGDIOBJ temp_pen = SelectObject(bdc,blue_pen);
  if (circle_fill) {
    HBRUSH blue_brush=CreateSolidBrush(RGB(100,100,255));
    HGDIOBJ temp_brush = SelectObject(bdc,blue_brush);
    Ellipse(bdc,x-10,y-10,x+10,y+10);
    SelectObject(bdc,temp_brush);
    DeleteObject(blue_brush); }
  else
    Ellipse(bdc,x-10,y-10,x+10,y+10);
  SelectObject(bdc,temp_pen);
//////////////////////////////////////
//  *** drawing code ends here ***  //
//////////////////////////////////////

  // blit and clean up
  BitBlt(wdc,0,0,rect.right,rect.bottom,bdc,0,0,SRCCOPY);
  DeleteObject(blue_pen);
  DeleteDC(bdc);
  ReleaseDC(window,wdc);
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
      std::srand(unsigned(std::time(0)));
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

