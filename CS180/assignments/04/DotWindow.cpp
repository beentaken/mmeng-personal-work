// DotWindow.cpp
// -- implementation of "dot window" class
// cs180 2/08

#include <cmath>
#include "DotWindow.h"


const char* DotWindow::class_name = "DotWindow Class";


DotWindow::DotWindow(const char *title) : closed(false) {
  int screen_width = GetSystemMetrics(SM_CXSCREEN),
      screen_height = GetSystemMetrics(SM_CYSCREEN),
      window_width = screen_width/4,
      window_height = screen_height/4;
  dot_radius = int(std::sqrt(0.01*screen_width*screen_height));
  dot_brush = CreateSolidBrush(RGB(255,0,0));
  HDC dc = GetDC(0);
  buffer_dc = CreateCompatibleDC(dc);
  back_buffer = CreateCompatibleBitmap(dc,window_width,window_height);
  ReleaseDC(0,dc);
  SelectObject(buffer_dc,back_buffer);
  SelectObject(buffer_dc,dot_brush);
  RECT rect = {0,0,window_width,window_height};
  FillRect(buffer_dc,&rect,HBRUSH(GetStockObject(WHITE_BRUSH)));

  WNDCLASS wc;
  wc.style = 0;
  wc.lpfnWndProc = WinProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(DotWindow*);
  wc.hInstance = 0;
  wc.hIcon = LoadIcon(0,IDI_APPLICATION);
  wc.hCursor = LoadCursor(0,IDC_ARROW);
  wc.hbrBackground = 0;
  wc.lpszMenuName = 0;
  wc.lpszClassName = class_name;
  RegisterClass(&wc);
  window = CreateWindow(class_name,title,
             WS_BORDER|WS_CAPTION|WS_SYSMENU,
             CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
             0,0,0,0);
  SetWindowLong(window,0,reinterpret_cast<long>(this));
  POINT point = {0,0};
  ClientToScreen(window,&point);
  rect.left = point.x;
  rect.top = point.y;
  rect.right = point.x + window_width;
  rect.bottom = point.y + window_height;
  AdjustWindowRect(&rect,WS_BORDER|WS_CAPTION|WS_SYSMENU,FALSE);
  MoveWindow(window,rect.left,rect.top,rect.right-rect.left,
             rect.bottom-rect.top,FALSE);
  ShowWindow(window,SW_SHOW);
}


DotWindow::~DotWindow(void) {
  if (!closed)
    DestroyWindow(window);
  DeleteDC(buffer_dc);
  DeleteObject(back_buffer);
  DeleteObject(dot_brush);
  UnregisterClass(class_name,0);
}


void DotWindow::SetDotPosition(int x, int y) {
  MSG msg;
  if (PeekMessage(&msg,window,0,0,PM_REMOVE))
    DispatchMessage(&msg);
  if (closed)
    return;
  RECT rect;
  GetClientRect(window,&rect);
  FillRect(buffer_dc,&rect,HBRUSH(GetStockObject(WHITE_BRUSH)));
  POINT point = {x,y};
  ScreenToClient(window,&point);
  Ellipse(buffer_dc,point.x-dot_radius,point.y-dot_radius,
          point.x+dot_radius,point.y+dot_radius);
  HDC dc = GetDC(window);
  BitBlt(dc,0,0,rect.right,rect.bottom,buffer_dc,0,0,SRCCOPY);
  ReleaseDC(window,dc);
}


bool DotWindow::IsClosed(void) {
  return closed;
}


LRESULT CALLBACK DotWindow::WinProc(HWND win, UINT msg,
                                    WPARAM wp, LPARAM lp) {
  switch (msg) {

    case WM_PAINT: {
      DotWindow *dw = reinterpret_cast<DotWindow*>(GetWindowLong(win,0));
      PAINTSTRUCT ps;
      HDC dc = BeginPaint(win,&ps);
      BitBlt(dc,ps.rcPaint.left,ps.rcPaint.top,
             ps.rcPaint.right-ps.rcPaint.left,
	           ps.rcPaint.bottom-ps.rcPaint.top,
	           dw->buffer_dc,ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);
      EndPaint(win,&ps);
      return 0; }

    case WM_DESTROY:
      DotWindow *dw = reinterpret_cast<DotWindow*>(GetWindowLong(win,0));
      dw->closed = true;
      PostQuitMessage(0);
      return 0;
  }

  return DefWindowProc(win,msg,wp,lp);
}
