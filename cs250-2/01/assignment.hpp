#pragma once
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <vector>

#include <windows.h>
#include <gdiplus.h>

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
    int width;

    std::vector<Point> myCubeVertices;
};

#endif // ASSIGNMENT_H

