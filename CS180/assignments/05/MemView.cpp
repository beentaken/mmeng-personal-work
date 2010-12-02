// MemView.cpp
// -- graphical view of heap (uses MemoryManager class)
// cs180 2/09
//
// To compile:
//   cl /EHsc /W3 MemView.cpp MemoryManager.cpp user32.lib gdi32.lib

#include <sstream>
#include <list>
#include <string>
#include <windows.h>
#include "MemoryManager.h"
using namespace std;


struct MemView {
  MemView(HINSTANCE, int);
  ~MemView(void);
  const char *name;
  static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
  HINSTANCE hinstance;
  HBITMAP back_buffer;
  HDC back_buffer_dc;
  RECT buffer_rect;
  void DrawHeap(const RECT&, MemoryManager&);
  const int heap_size;
  static const int MENU_TESTS_TEST1 = 100,
                   MENU_TESTS_TEST2 = 110,
                   MENU_TESTS_TEST3 = 120;
  static const int MENU_COUNT_16    = 216,
                   MENU_COUNT_32    = 232,
                   MENU_COUNT_64    = 264,
                   MENU_COUNT_128   = 328,
                   MENU_COUNT_256   = 456;
  HMENU menu_count;
  int cell_count;
  void DrawTest1(void);
  void DrawTest2(void);
  void DrawTest3(void);
};


int WINAPI WinMain(HINSTANCE instance, HINSTANCE ignore,
                   LPSTR command_line, int show) {
  MemView *memview = new MemView(instance,show);

  MSG msg;
  while (GetMessage(&msg,0,0,0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  delete memview;
  return msg.wParam;
}


MemView::MemView(HINSTANCE hinst, int show)
    : hinstance(hinst), name("Heap viewer"), back_buffer(0),
      heap_size(1<<20), cell_count(32) {

  WNDCLASS wc;
  wc.style = 0;
  wc.lpfnWndProc = WinProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(MemView*);
  wc.hInstance = hinstance;
  wc.hIcon = LoadIcon(0,IDI_APPLICATION);
  wc.hCursor = LoadCursor(0,IDC_ARROW);
  wc.hbrBackground = 0;
  wc.lpszMenuName = 0;
  wc.lpszClassName = name;
  RegisterClass(&wc);
  HMENU menu = CreateMenu();
  HMENU menu_tests = CreatePopupMenu();
    AppendMenu(menu_tests,MF_STRING,MENU_TESTS_TEST1,"Test #1");
    AppendMenu(menu_tests,MF_STRING,MENU_TESTS_TEST2,"Test #2");
    AppendMenu(menu_tests,MF_STRING,MENU_TESTS_TEST3,"Test #3");
  menu_count = CreatePopupMenu();
    AppendMenu(menu_count,MF_STRING,MENU_COUNT_16,"16");
    AppendMenu(menu_count,MF_STRING,MENU_COUNT_32,"32");
    CheckMenuItem(menu_count,MENU_COUNT_32,MF_CHECKED);
    AppendMenu(menu_count,MF_STRING,MENU_COUNT_64,"64");
    AppendMenu(menu_count,MF_STRING,MENU_COUNT_128,"128");
    AppendMenu(menu_count,MF_STRING,MENU_COUNT_256,"256");
  AppendMenu(menu,MF_POPUP|MF_STRING,(UINT)menu_tests,"Tests");
  AppendMenu(menu,MF_POPUP|MF_STRING,(UINT)menu_count,"Count");
  RECT rect = {0,0,0,0};
  rect.right = 256*(GetSystemMetrics(SM_CXSCREEN)/512);
  rect.bottom = rect.right;
  AdjustWindowRect(&rect,WS_CAPTION|WS_SYSMENU,TRUE);
  HWND win = CreateWindow(name,name,WS_CAPTION|WS_SYSMENU,
                          CW_USEDEFAULT,CW_USEDEFAULT,
                          rect.right-rect.left,rect.bottom-rect.top,
                          0,menu,hinstance,this);
  ShowWindow(win,show);
}


MemView::~MemView(void) {
  if (back_buffer) {
	  DeleteDC(back_buffer_dc);
	  DeleteObject(back_buffer);
  }
  UnregisterClass(name,hinstance);
}


LRESULT CALLBACK MemView::WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp) {
  static MemView *mv = 0;

  switch (msg) {

    case WM_CREATE: {
      CREATESTRUCT *csp = reinterpret_cast<CREATESTRUCT*>(lp);
      mv = reinterpret_cast<MemView*>(csp->lpCreateParams);
      RECT rect;
      GetClientRect(win,&rect);
      HDC dc = GetDC(win);
      mv->back_buffer_dc = CreateCompatibleDC(dc);
      mv->back_buffer = CreateCompatibleBitmap(dc,rect.right,rect.bottom);
      mv->buffer_rect = rect;
      SelectObject(mv->back_buffer_dc,mv->back_buffer);
      FillRect(mv->back_buffer_dc,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
      return 0; }

    case WM_PAINT: {
      HDC dc;
      PAINTSTRUCT ps;
      dc = BeginPaint(win,&ps);
      RECT &rect = ps.rcPaint;
	    BitBlt(dc,rect.left,rect.top,rect.right-rect.left,
	           rect.bottom-rect.top,
	           mv->back_buffer_dc,rect.left,rect.top,SRCCOPY);
      EndPaint(win,&ps);
      return 0; }

    case WM_COMMAND:
      if (MENU_TESTS_TEST1 <= LOWORD(wp)
            && LOWORD(wp) <= MENU_TESTS_TEST3) {
        if (LOWORD(wp) == MENU_TESTS_TEST1)
          mv->DrawTest1();
        else if (LOWORD(wp) == MENU_TESTS_TEST2)
          mv->DrawTest2();
        else if (LOWORD(wp) == MENU_TESTS_TEST3)
          mv->DrawTest3();
        InvalidateRect(win,0,TRUE); }
      else if (MENU_COUNT_16 <= LOWORD(wp)
                 && LOWORD(wp) <= MENU_COUNT_256) {
        int old_item = 200 + mv->cell_count;
        CheckMenuItem(mv->menu_count,old_item,MF_UNCHECKED);
        CheckMenuItem(mv->menu_count,LOWORD(wp),MF_CHECKED);
        mv->cell_count = LOWORD(wp) - 200;
      }
      return 0;

    case WM_CHAR:
      if (wp == 0x1b)
        DestroyWindow(win);
      return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return DefWindowProc(win,msg,wp,lp);
}


struct BlockInfo {
  int start_address;
  int size;
  bool in_use;
};


void MemView::DrawHeap(const RECT& rect, MemoryManager& memory_manager) {
  stringstream ss;
  memory_manager.dump(ss);
  list<BlockInfo> blocks;
  ss >> hex;
  while (ss) {
    BlockInfo info;
    string str;
    ss >> str >> str >> info.start_address;
    ss >> str >> str >> info.size;
    ss >> str >> str;
    info.in_use = (str == "true");
    if (ss)
      blocks.push_back(info);
  }
  BlockInfo info = blocks.front();
  for (list<BlockInfo>::iterator i=blocks.begin(); i != blocks.end(); ++i) {
    i->start_address -= info.start_address;
  }

  int width = rect.right - rect.left,
      height = rect.bottom - rect.top;
  float scale = float(height)/heap_size;
  for (list<BlockInfo>::iterator i=blocks.begin(); i != blocks.end(); ++i) {
    HBRUSH brush = i->in_use ? (HBRUSH)GetStockObject(GRAY_BRUSH)
                             : (HBRUSH)GetStockObject(WHITE_BRUSH);
    int y = int(scale*float(i->start_address));
    RECT cell = {rect.left,y,rect.right,y + int(scale*i->size) + 1};
    FillRect(back_buffer_dc,&cell,brush);
    MoveToEx(back_buffer_dc,cell.left,cell.top,0);
    LineTo(back_buffer_dc,cell.right,cell.top);
  }
  SelectObject(back_buffer_dc,(HBRUSH)GetStockObject(NULL_BRUSH));
  Rectangle(back_buffer_dc,rect.left,rect.top,rect.right+1,rect.bottom+1);
}

void MemView::DrawTest1(void) {
  FillRect(back_buffer_dc,&buffer_rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
  MemoryManager memory_manager(heap_size);
  int width = buffer_rect.right/cell_count;
  RECT rect = {0,0,0,buffer_rect.bottom};
  for (int i=0; i < cell_count; ++i) {
    memory_manager.allocate((1 + i%2)*(heap_size/cell_count));
    rect.left = rect.right;
    rect.right += width;
    DrawHeap(rect,memory_manager);
  }
}


void MemView::DrawTest2(void) {
  FillRect(back_buffer_dc,&buffer_rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
  MemoryManager memory_manager(heap_size);
  int width = buffer_rect.right/cell_count;
  RECT rect = {0,0,0,buffer_rect.bottom};
  void *previous = 0;
  for (int i=0; i < cell_count; ++i) {
    switch (i%3) {
      case 0:
        previous = memory_manager.allocate((1+i%2)*heap_size/cell_count);
        break;
      case 1:
        memory_manager.allocate((1+i%2)*heap_size/cell_count);
        break;
      case 2:
        if (previous) {
          memory_manager.deallocate(previous);
          previous = 0;
        }
    }
    rect.left = rect.right;
    rect.right += width;
    DrawHeap(rect,memory_manager);
  }
}


void MemView::DrawTest3(void) {
  FillRect(back_buffer_dc,&buffer_rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
  MemoryManager memory_manager(heap_size);
  int width = buffer_rect.right/cell_count;
  RECT rect = {0,0,0,buffer_rect.bottom};
  void *previous[4] = {0,0,0,0};
  for (int i=0,j=0,k=0; i < cell_count; ++i,j=(j+1)%4,k=(k+1)%7) {
    switch (i%5) {
      case 0:
      case 1:
      case 2:
        previous[j] = memory_manager.allocate((k+1)*heap_size/cell_count);
        break;
      case 3:
      case 4:
        if (previous[j]) {
          memory_manager.deallocate(previous[j]);
          previous[j] = 0;
        }
    }
    rect.left = rect.right;
    rect.right += width;
    DrawHeap(rect,memory_manager);
  }
}
