// Compute.cpp
// -- implementation of dot position updater
// cs180 2/08

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
#include "Compute.h"


double drand(void) {
  return double(rand())/double(RAND_MAX);
}


Compute::Compute(void) {
  current_time = GetTickCount();
  double speed = 0.25*GetSystemMetrics(SM_CXSCREEN);
  double angle = 8.0*std::atan(1.0)*drand();
  velocity_x = speed*std::cos(angle);
  velocity_y = speed*std::sin(angle);
  int screen_width = GetSystemMetrics(SM_CXSCREEN);
  int screen_height =  GetSystemMetrics(SM_CYSCREEN);
  position_x = screen_width*drand();
  position_y =screen_height*drand();
  offset = int(std::sqrt(0.01*screen_width*screen_height));
}


Compute::~Compute(void) {
}


void Compute::operator()(double& x, double& y) {
  int time = GetTickCount();
  double dt = 0.001*(time - current_time);
  current_time = time;
  position_x += velocity_x*dt;
  double xmax = GetSystemMetrics(SM_CXSCREEN) - offset;
  if (position_x < offset) {
    position_x += 2*(offset-position_x);
    velocity_x = -velocity_x;
  }
  if (position_x > xmax) {
    position_x -= 2*(position_x - xmax);
    velocity_x = -velocity_x;
  }
  position_y += velocity_y*dt;
  double ymax = GetSystemMetrics(SM_CYSCREEN) - offset;
  if (position_y < offset) {
    position_y += 2*(offset-position_y);
    velocity_y = -velocity_y;
  }
  if (position_y > ymax) {
    position_y -= 2*(position_y - ymax);
    velocity_y = -velocity_y;
  }
  x = position_x;
  y = position_y;
}
