// DotWindow.h
// -- interface for the "dot window"
// cs180 2/08

#ifndef CS180_DOT
#define CS180_DOT

#include <windows.h>


class DotWindow {
  public:
    DotWindow(const char* title);
    ~DotWindow(void);
    void SetDotPosition(int x, int y);
    bool IsClosed(void);
  private:
    static const char *class_name;
    int dot_radius;
    bool closed;
    HWND window;
    HBITMAP back_buffer;
    HDC buffer_dc;
    HBRUSH dot_brush;
    static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
};


#endif
