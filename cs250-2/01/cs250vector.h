// cs250vector.h
// -- points and vector
// cs250 5/12

#ifndef CS250VECTOR_H
#define CS250VECTOR_H


struct Point;
struct Vector;


struct Point {
  float x, y, z, w;
  Point(void);
  Point(float,float,float);
};


struct Vector {
  float x, y, z, w;
  Vector(void);
  Vector(float,float,float);
  bool Normalize(void);
};


Vector operator+(const Vector&, const Vector&);
Point  operator+(const Point&, const Vector&);
Vector operator-(const Vector&);
Vector operator-(const Point&, const Point&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(float, const Vector&);
Point operator* (float, const Point&);
float  operator*(const Vector&, const Vector&);
float  abs(const Vector&);
Vector operator^(const Vector&, const Vector&);

Point OrthProj(const Point&);
Point PersProj(const Point&);


#endif

