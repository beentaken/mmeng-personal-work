#include "cs250transform.h"

#include <cstring> // memset
#include <functional> // plus
#include <numeric> // inner_product
#include <algorithm> // transform

Transform::Transform(void)
{
    // Build identity matrix.
    std::memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < 4; ++i)
    {
        matrix[i][i] = 1;
    }
}

Transform::Transform(const Vector& c1, const Vector& c2, const Vector& c3)
{
    // Can't just memcpy things over...
    matrix[0][0] = c1.x;
    matrix[0][1] = c2.x;
    matrix[0][2] = c3.x;

    matrix[1][0] = c1.y;
    matrix[1][1] = c2.y;
    matrix[1][2] = c3.y;

    matrix[2][0] = c1.z;
    matrix[2][1] = c2.z;
    matrix[2][2] = c3.z;

    matrix[3][0] = c1.w;
    matrix[3][1] = c2.w;
    matrix[3][2] = c3.w;

    matrix[0][3] = 0;
    matrix[1][3] = 0;
    matrix[2][3] = 0;
    matrix[3][3] = 1;
}

namespace
{
    template <typename BinaryOperator>
    Transform ApplyToLinear(const Transform& lhs, const Transform& rhs, BinaryOperator&& op)
    {
        Transform output;
        for (int i = 0; i < 3; ++i)
        {
            std::transform(lhs.matrix[i], lhs.matrix[i]+3, rhs.matrix[i], output.matrix[i], op);
        }
        return(output);
    }
}

Transform operator+(const Transform& lhs, const Transform& rhs)
{
    // Sums just the linear part?
    return(ApplyToLinear(lhs, rhs, std::plus<float>()));
}

Transform operator-(const Transform& lhs, const Transform& rhs)
{
    return(ApplyToLinear(lhs, rhs, std::minus<float>()));
}

Transform operator*(float lhs, const Transform& rhs)
{
    Transform to_return;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            to_return.matrix[i][j] = lhs * rhs.matrix[i][j];
        }
    }

    return(to_return);
}

Transform operator*(const Transform& lhs, const Transform& rhs)
{
    Transform to_return;

    to_return.matrix[0][0] = lhs.matrix[0][0] * rhs.matrix[0][0] + lhs.matrix[0][1] * rhs.matrix[1][0] + lhs.matrix[0][2] * rhs.matrix[2][0] + lhs.matrix[0][3] * rhs.matrix[3][0]; 
    to_return.matrix[0][1] = lhs.matrix[0][0] * rhs.matrix[0][1] + lhs.matrix[0][1] * rhs.matrix[1][1] + lhs.matrix[0][2] * rhs.matrix[2][1] + lhs.matrix[0][3] * rhs.matrix[3][1]; 
    to_return.matrix[0][2] = lhs.matrix[0][0] * rhs.matrix[0][2] + lhs.matrix[0][1] * rhs.matrix[1][2] + lhs.matrix[0][2] * rhs.matrix[2][2] + lhs.matrix[0][3] * rhs.matrix[3][2]; 
    to_return.matrix[0][3] = lhs.matrix[0][0] * rhs.matrix[0][3] + lhs.matrix[0][1] * rhs.matrix[1][3] + lhs.matrix[0][2] * rhs.matrix[2][3] + lhs.matrix[0][3] * rhs.matrix[3][3]; 
    to_return.matrix[1][0] = lhs.matrix[1][0] * rhs.matrix[0][0] + lhs.matrix[1][1] * rhs.matrix[1][0] + lhs.matrix[1][2] * rhs.matrix[2][0] + lhs.matrix[1][3] * rhs.matrix[3][0]; 
    to_return.matrix[1][1] = lhs.matrix[1][0] * rhs.matrix[0][1] + lhs.matrix[1][1] * rhs.matrix[1][1] + lhs.matrix[1][2] * rhs.matrix[2][1] + lhs.matrix[1][3] * rhs.matrix[3][1]; 
    to_return.matrix[1][2] = lhs.matrix[1][0] * rhs.matrix[0][2] + lhs.matrix[1][1] * rhs.matrix[1][2] + lhs.matrix[1][2] * rhs.matrix[2][2] + lhs.matrix[1][3] * rhs.matrix[3][2]; 
    to_return.matrix[1][3] = lhs.matrix[1][0] * rhs.matrix[0][3] + lhs.matrix[1][1] * rhs.matrix[1][3] + lhs.matrix[1][2] * rhs.matrix[2][3] + lhs.matrix[1][3] * rhs.matrix[3][3]; 
    to_return.matrix[2][0] = lhs.matrix[2][0] * rhs.matrix[0][0] + lhs.matrix[2][1] * rhs.matrix[1][0] + lhs.matrix[2][2] * rhs.matrix[2][0] + lhs.matrix[2][3] * rhs.matrix[3][0]; 
    to_return.matrix[2][1] = lhs.matrix[2][0] * rhs.matrix[0][1] + lhs.matrix[2][1] * rhs.matrix[1][1] + lhs.matrix[2][2] * rhs.matrix[2][1] + lhs.matrix[2][3] * rhs.matrix[3][1]; 
    to_return.matrix[2][2] = lhs.matrix[2][0] * rhs.matrix[0][2] + lhs.matrix[2][1] * rhs.matrix[1][2] + lhs.matrix[2][2] * rhs.matrix[2][2] + lhs.matrix[2][3] * rhs.matrix[3][2]; 
    to_return.matrix[2][3] = lhs.matrix[2][0] * rhs.matrix[0][3] + lhs.matrix[2][1] * rhs.matrix[1][3] + lhs.matrix[2][2] * rhs.matrix[2][3] + lhs.matrix[2][3] * rhs.matrix[3][3]; 
    to_return.matrix[3][0] = lhs.matrix[3][0] * rhs.matrix[0][0] + lhs.matrix[3][1] * rhs.matrix[1][0] + lhs.matrix[3][2] * rhs.matrix[2][0] + lhs.matrix[3][3] * rhs.matrix[3][0]; 
    to_return.matrix[3][1] = lhs.matrix[3][0] * rhs.matrix[0][1] + lhs.matrix[3][1] * rhs.matrix[1][1] + lhs.matrix[3][2] * rhs.matrix[2][1] + lhs.matrix[3][3] * rhs.matrix[3][1]; 
    to_return.matrix[3][2] = lhs.matrix[3][0] * rhs.matrix[0][2] + lhs.matrix[3][1] * rhs.matrix[1][2] + lhs.matrix[3][2] * rhs.matrix[2][2] + lhs.matrix[3][3] * rhs.matrix[3][2]; 
    to_return.matrix[3][3] = lhs.matrix[3][0] * rhs.matrix[0][3] + lhs.matrix[3][1] * rhs.matrix[1][3] + lhs.matrix[3][2] * rhs.matrix[2][3] + lhs.matrix[3][3] * rhs.matrix[3][3];

    return(to_return);
}

// TODO: Split into explicit transpose function.
Transform operator*(const Transform& mat)
{
    Transform to_return;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            to_return.matrix[i][j] = mat.matrix[j][i];
        }
    }

    return(to_return);
}

Vector operator*(const Transform& lhs, const Vector& rhs)
{
    Vector to_return;
    to_return.x = std::inner_product(lhs.matrix[0], lhs.matrix[0]+4, &rhs.x, 0.0f);
    to_return.y = std::inner_product(lhs.matrix[1], lhs.matrix[1]+4, &rhs.x, 0.0f);
    to_return.x = std::inner_product(lhs.matrix[2], lhs.matrix[2]+4, &rhs.x, 0.0f);
    to_return.w = std::inner_product(lhs.matrix[3], lhs.matrix[3]+4, &rhs.x, 0.0f);

    return(to_return);
}

Point operator*(const Transform& lhs, const Point& rhs)
{
    Point to_return;
    to_return.x = std::inner_product(lhs.matrix[0], lhs.matrix[0]+4, &rhs.x, 0.0f);
    to_return.y = std::inner_product(lhs.matrix[1], lhs.matrix[1]+4, &rhs.x, 0.0f);
    to_return.x = std::inner_product(lhs.matrix[2], lhs.matrix[2]+4, &rhs.x, 0.0f);
    to_return.w = std::inner_product(lhs.matrix[3], lhs.matrix[3]+4, &rhs.x, 0.0f);

    return(to_return);

}

float Trace(const Transform& t)
{
    // Only linear part?
    return(t.matrix[0][0] + t.matrix[1][1] + t.matrix[2][2]);
}

Transform RotX(float angle)
{
    Vector c1(1.0f, 0.0f, 0.0f);
    Vector c2(0.0f, std::cos(angle), std::sin(angle));
    Vector c3(0.0f, -std::sin(angle), std::cos(angle));

    return(Transform(c1, c2, c3));
}

Transform RotY(float angle)
{
    Vector c1(std::cos(angle), 0.0f, -std::sin(angle));
    Vector c2(0.0f, 1.0f, 0.0f);
    Vector c3(std::sin(angle), 0.0f, std::cos(angle));

    return(Transform(c1, c2, c3));
}

Transform RotZ(float angle)
{
    Vector c1(std::cos(angle), std::sin(angle), 0.0f);
    Vector c2(-std::sin(angle), std::cos(angle), 0.0f);
    Vector c3(0.0f,0.0f,1.0f);

    return(Transform(c1, c2, c3));
}

Transform Rot(Vector axis, float angle)
{
    axis.Normalize();

    float a = std::cos(angle);
    float b = std::sin(angle);
    float c = 1.0f - a;

    Vector c1(c * axis.x*axis.x + a, c * axis.x*axis.y - b*axis.z, c*axis.x*axis.y + b*axis.y);
    Vector c2(c * axis.x*axis.y + b*axis.z, c*axis.y*axis.y + a, c * axis.y*axis.z - b*axis.x);
    Vector c3(c * axis.x*axis.z - b*axis.y, c*axis.y*axis.z + b * axis.x, c*axis.z*axis.z + a);

    return(Transform(c1, c2, c3));
}

Transform Proj(Vector n)
{
    // Ortho projection onto a plane.
    n.Normalize();

    Transform t1, t2;

    t1.matrix[0][0] = n.x;
    t1.matrix[1][0] = n.y;
    t1.matrix[2][0] = n.z;

    t2.matrix[0][0] = n.x;
    t2.matrix[0][1] = n.y;
    t2.matrix[0][2] = n.z;

    Transform result = t1 * t2;

    for (int i = 0; i < 3; ++i)
    {
        result.matrix[i][i] = 1.0f - result.matrix[i][i];
    }

    return result;
}

Transform Refl(Vector n)
{
    n.Normalize();

    Vector c1(1.0f - 2.0f * n.x * n.x, -2.0f * n.x * n.y, -2.0f * n.x * n.z);
    Vector c2(-2.0f * n.x * n.y, 1.0f - 2.0f * n.y * n.y, -2.0f * n.y * n.z);
    Vector c3(-2.0f * n.x * n.z, -2.0f * n.y * n.z, 1.0f - 2.0f * n.z * n.z);

    return Transform(c1, c2, c3);
}

