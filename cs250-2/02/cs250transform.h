// cs250transform.h
// -- linear transformations
// cs250 5/12

#ifndef CS250TRANSFORM_H
#define CS250TRANFORM_H

#include "cs250vector.h"

struct Transform {
  float matrix[4][4];
  Transform(void);
  Transform(const Vector&, const Vector&, const Vector&);
};


Transform operator+(const Transform&, const Transform&);
Transform operator-(const Transform&, const Transform&);
Transform operator*(float, const Transform&);
Transform operator*(const Transform&, const Transform&);
Transform operator*(const Transform&);
Vector operator*(const Transform&, const Vector&);
Point operator*(const Transform&, const Point&);
float Trace(const Transform&);
Transform RotX(float);
Transform RotY(float);
Transform RotZ(float);
Transform Rot(Vector, float);
Transform Proj(Vector);
Transform Refl(Vector);


#endif

