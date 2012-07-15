#include "cs250vector.h"
#include <cmath>

Point::Point()
    :x(0), y(0), z(0), w(1)
{
}

Point::Point(float x_, float y_, float z_)
    :x(x_), y(y_), z(z_), w(1)
{
}

Vector::Vector()
    :x(0), y(0), z(0), w(0)
{
}

// This really needs to have a user definable w, since otherwise how do we
// hold plane equations for culling or stuff?
Vector::Vector(float x_, float y_, float z_)
    :x(x_), y(y_), z(z_), w(0)
{
}

bool Vector::Normalize()
{
    if (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f)
    {
        return(false);
    }

    float intermediate = std::sqrt(x*x + y*y + z*z + w*w);
    x /= intermediate;
    y /= intermediate;
    z /= intermediate;

    return(true);
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
    return(Vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z));
}

Point  operator+(const Point& lhs, const Vector& rhs)
{
    return(Point(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z));
}

Vector operator-(const Vector& vec)
{
    return(Vector(-vec.x, -vec.y, -vec.z));
}

Vector operator-(const Point& lhs, const Point& rhs)
{
    return(Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z));
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return(Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z));
}

Vector operator*(float lhs, const Vector& rhs)
{
    return(Vector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z));
}

Point operator*(float lhs, const Point& rhs)
{
    // No C++11 uniform constructor syntax in MSVC...
    //return{lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
    return(Point(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z));
}

// This is a really bad idea. Overloaded operators should work like int
// operators. Duplicate this into an explicit function later!
// *FIXME FIXME*
float  operator*(const Vector& lhs, const Vector& rhs)
{
    return(lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w);
}

// TODO: This needs a better name, really.
float abs(const Vector& vec)
{
    return(sqrt(vec * vec));
}

// Similar issue to dot product, make this an explicit function, not an
// overload.
// *FIXME FIXME*
Vector operator^(const Vector& lhs, const Vector& rhs)
{
    return(Vector(lhs.y * rhs.z - rhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x));
}

Point OrthProj(const Point& p)
{
    return (Point(p.x, p.y, 0));
}

Point PersProj(const Point& p)
{
    return(Point(p.x / (1 - p.z), p.y / (1 - p.z), 0));
}

