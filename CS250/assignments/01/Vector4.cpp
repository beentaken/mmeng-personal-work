#include "Vector4.h"

#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

namespace
{
    const unsigned VECTORSIZE = 4;

    class EpsilonComparer
    {
        public:
            bool operator()(const f32& first, const f32& second) const
            {
                return(std::abs(first - second) < EPSILON);
            }
    };
}

void Vector4::Print(void) const
{
  printf("%5.3f, %5.3f, %5.3f, %5.3f\n",x,y,z,w);
}

Vector4::Vector4()
{
    Zero();
}

Vector4::Vector4(const Vector4& rhs)
{
    std::copy(rhs.v, rhs.v + VECTORSIZE, v);
}

Vector4::Vector4(f32 xx, f32 yy, f32 zz, f32 ww)
    :x(xx), y(yy), z(zz), w(ww)
{
}

Vector4& Vector4::operator=(const Vector4& rhs)
{
    std::copy(rhs.v, rhs.v + VECTORSIZE, v);

    return(*this);
}

Vector4 Vector4::operator-() const
{
    Vector4 to_return;

    std::transform(v, v+VECTORSIZE, to_return.v, std::bind2nd(std::multiplies<f32>(), -1));

    return(to_return);
}

Vector4 Vector4::operator+(const Vector4& rhs) const
{
    Vector4 to_return(*this);

    to_return += rhs;

    return(to_return);
}

Vector4 Vector4::operator-(const Vector4& rhs) const
{
    Vector4 to_return(*this);

    to_return -= rhs;

    return(to_return);
}

Vector4 Vector4::operator*(const f32 rhs) const
{
    Vector4 to_return(*this);

    to_return *= rhs;

    return(to_return);
}

Vector4 Vector4::operator/(const f32 rhs) const
{
    Vector4 to_return(*this);

    to_return /= rhs;

    return(to_return);
}

Vector4& Vector4::operator+=(const Vector4& rhs)
{
    std::transform(v, v+VECTORSIZE, rhs.v, v, std::plus<f32>());
    return(*this);
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
    std::transform(v, v+VECTORSIZE, rhs.v, v, std::minus<f32>());
    return(*this);
}

Vector4& Vector4::operator*=(const f32 rhs)
{
    std::transform(v, v+VECTORSIZE, v, std::bind2nd(std::multiplies<f32>(), rhs));
    return(*this);
}

Vector4& Vector4::operator/=(const f32 rhs)
{
    std::transform(v, v+VECTORSIZE, v, std::bind2nd(std::divides<f32>(), rhs));
    return(*this);
}

bool Vector4::operator==(const Vector4& rhs) const
{
    return(std::equal(v, v+VECTORSIZE, rhs.v, EpsilonComparer()));
}

bool Vector4::operator!=(const Vector4& rhs) const
{
    return(!(*this == rhs));
}

f32 Vector4::Dot(const Vector4& rhs) const
{
    return(std::inner_product(v, v+VECTORSIZE, rhs.v, 0));
}

Vector4 Vector4::Cross(const Vector4& rhs) const
{
    Vector4 to_return(rhs);

    // TODO
    //

    to_return.x = 0; // BAAAAH
    return(to_return);
}

f32 Vector4::Length() const
{
    return(std::sqrt(LengthSq()));
}

f32 Vector4::LengthSq() const
{
    return(std::inner_product(v, v+VECTORSIZE, v, 0));
}

void Vector4::Normalize()
{
    f32 magnitude = Length();

    std::transform(v, v+VECTORSIZE, v, std::bind2nd(std::divides<f32>(), magnitude));
}

void Vector4::Zero()
{
    std::fill(v, v+VECTORSIZE, 0);
}

