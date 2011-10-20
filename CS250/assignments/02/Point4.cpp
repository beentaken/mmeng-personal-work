#include "Point4.h"

#include "Vector4.h"

#include <algorithm>
#include <functional>

namespace
{
    const unsigned VECTORSIZE = 4;

    class EpsilonComparer
    {
        public:
            bool operator()(const f32 &first, const f32& second) const
            {
                return(std::abs(first - second) < EPSILON);
            }
    };
}

void Point4::Print(void) const
{
  printf("%5.3f, %5.3f, %5.3f, %5.3f\n",x,y,z,w);
}

Point4::Point4()
{
    Zero();
	w = 1.0f;
}

Point4::Point4(const Point4& rhs)
{
    std::copy(rhs.v, rhs.v+VECTORSIZE, v);
}

Point4::Point4(f32 xx, f32 yy, f32 zz, f32 ww)
    :x(xx), y(yy), z(zz), w(ww)
{
}

Point4& Point4::operator=(const Point4& rhs)
{
    std::copy(rhs.v, rhs.v+VECTORSIZE, v);

    return(*this);
}

Point4 Point4::operator-() const
{
    Point4 to_return;

    std::transform(v, v+VECTORSIZE, to_return.v, std::bind2nd(std::multiplies<f32>(), -1));

    return(to_return);
}

Vector4 Point4::operator-(const Point4& rhs) const
{
    return(Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w));
}

Point4 Point4::operator+(const Vector4& rhs) const
{
    Point4 to_return(*this);

    to_return += rhs;

    return(to_return);
}

Point4 Point4::operator-(const Vector4& rhs) const
{
    Point4 to_return(*this);

    to_return -= rhs;

    return(to_return);
}

Point4& Point4::operator+=(const Vector4& rhs)
{
    std::transform(v, v+VECTORSIZE, rhs.v, v, std::plus<f32>());

    return(*this);
}

Point4& Point4::operator-=(const Vector4& rhs)
{
    std::transform(v, v+VECTORSIZE, rhs.v, v, std::minus<f32>());

    return(*this);
}

bool Point4::operator==(const Point4& rhs) const
{
    return(std::equal(v, v+VECTORSIZE, rhs.v, EpsilonComparer()));
}

bool Point4::operator!=(const Point4& rhs) const
{
    return(!(*this == rhs));
}

void Point4::Zero()
{
    std::fill(v, v+VECTORSIZE - 1, 0);
    v[3] = 1;
}

