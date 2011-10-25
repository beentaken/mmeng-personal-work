#include "Matrix4.h"

#include "Vector4.h"
#include "Point4.h"

#include <algorithm>
#include <functional>
#include <numeric>

namespace
{
    const unsigned VECTORSIZE = 16;

    class EpsilonComparer
    {
        public:

            bool operator()(const f32& first, const f32& second) const
            {
                return (std::fabs(first - second) < EPSILON);
            }
    };
}

void Matrix4::Print(void) const
{
  printf("--------------------------\n");
  printf("%5.3f %5.3f %5.3f %5.3f\n", m00, m01, m02, m03 );
  printf("%5.3f %5.3f %5.3f %5.3f\n", m10, m11, m12, m13 );
  printf("%5.3f %5.3f %5.3f %5.3f\n", m20, m21, m22, m23 );
  printf("%5.3f %5.3f %5.3f %5.3f\n", m30, m31, m32, m33 );
  printf("--------------------------\n");
}

Matrix4::Matrix4()
{
    Zero();
}

Matrix4::Matrix4(const Matrix4& rhs)
{
    std::copy(rhs.v, rhs.v+VECTORSIZE, v);
}

Matrix4::Matrix4(f32 mm00, f32 mm01, f32 mm02, f32 mm03,
        f32 mm10, f32 mm11, f32 mm12, f32 mm13,
        f32 mm20, f32 mm21, f32 mm22, f32 mm23,
        f32 mm30, f32 mm31, f32 mm32, f32 mm33)
{
    m[0][0] = mm00;
    m[0][1] = mm01;
    m[0][2] = mm02;
    m[0][3] = mm03;

    m[1][0] = mm10;
    m[1][1] = mm11;
    m[1][2] = mm12;
    m[1][3] = mm13;

    m[2][0] = mm20;
    m[2][1] = mm21;
    m[2][2] = mm22;
    m[2][3] = mm23;

    m[3][0] = mm30;
    m[3][1] = mm31;
    m[3][2] = mm32;
    m[3][3] = mm33;
}
  
Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
    std::copy(rhs.v, rhs.v+VECTORSIZE, v);

    return(*this);
}

Vector4 Matrix4::operator*(const Vector4& rhs) const
{
    return(Vector4(std::inner_product(rhs.v, rhs.v+4, v+0, 0),
                   std::inner_product(rhs.v, rhs.v+4, v+4, 0),
                   std::inner_product(rhs.v, rhs.v+4, v+8, 0),
                   std::inner_product(rhs.v, rhs.v+4, v+12, 0)
                   )
            );
}

Point4 Matrix4::operator*(const Point4& rhs) const
{
    return(Point4(std::inner_product(rhs.v, rhs.v+4, v+0, 0),
                  std::inner_product(rhs.v, rhs.v+4, v+4, 0),
                  std::inner_product(rhs.v, rhs.v+4, v+8, 0),
                  std::inner_product(rhs.v, rhs.v+4, v+12, 0)
                  )
            );

}

Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
    Matrix4 to_return(rhs);

    to_return += *this;

    return(to_return);
}

Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
    Matrix4 to_return(rhs);

    to_return -= *this;

    return(to_return);
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
    Matrix4 to_return;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                to_return.m[i][j] += m[i][k] * rhs.m[k][j];
            }
        }
    }

    return(to_return);
}

Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    std::transform(rhs.v, rhs.v + VECTORSIZE, v, v, std::plus<f32>());

    return(*this);
}

Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    std::transform(rhs.v, rhs.v + VECTORSIZE, v, v, std::minus<f32>());

    return(*this);
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    Matrix4 temp = *this * rhs;

    *this = temp;

    return(*this);
}

Matrix4 Matrix4::operator*(const f32 rhs) const
{
    Matrix4 to_return(*this);

    to_return *= rhs;

    return(to_return);
}

Matrix4 Matrix4::operator/(const f32 rhs) const
{
    Matrix4 to_return(*this);

    to_return /= rhs;

    return(to_return);
}

Matrix4& Matrix4::operator*=(const f32 rhs)
{
    std::transform(v, v+VECTORSIZE, v, std::bind2nd(std::multiplies<f32>(), rhs));

    return(*this);
}

Matrix4& Matrix4::operator/=(const f32 rhs)
{
    std::transform(v, v+VECTORSIZE, v, std::bind2nd(std::divides<f32>(), rhs));

    return(*this);
}

bool Matrix4::operator==(const Matrix4& rhs) const
{
    return(std::equal(v, v+VECTORSIZE, rhs.v, EpsilonComparer()));
}

bool Matrix4::operator!=(const Matrix4& rhs) const
{
    return(!(*this == rhs));
}

void Matrix4::Zero()
{
    std::fill(v, v+VECTORSIZE, 0);
}

void Matrix4::Identity()
{
    Zero();
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

