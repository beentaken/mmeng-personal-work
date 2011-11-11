#include "transformations.hpp"
#include <cmath>

namespace mat4
{
     Matrix4 scale(Vector4 scale_factors)
	{
		Matrix4 to_return;
		to_return.m[0][0] = scale_factors.x;
		to_return.m[1][1] = scale_factors.y;
		to_return.m[2][2] = scale_factors.z;
		to_return.m[3][3] = 1.0f;

		return(to_return);
	}

	Matrix4 rotate_x(float angle)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[1][1] = std::cos(angle);
		to_return.m[2][2] = to_return.m[1][1];
		to_return.m[1][2] = -std::sin(angle);
		to_return.m[2][1] = -to_return.m[1][2];

		return(to_return);
	}

	Matrix4 rotate_y(float angle)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[0][0] = std::cos(angle);
		to_return.m[2][2] = to_return.m[0][0];
		to_return.m[0][2] = std::sin(angle);
		to_return.m[2][0] = -to_return.m[0][2];

		return(to_return);
	}

	Matrix4 rotate_z(float angle)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[0][0] = std::cos(angle);
		to_return.m[1][1] = to_return.m[0][0];
		to_return.m[0][1] = -std::sin(angle);
		to_return.m[1][0] = -to_return.m[0][1];

		return(to_return);
	}

	Matrix4 rotate(Vector4 angles)
	{
		return(rotate_x(angles.x) * rotate_y(angles.y) * rotate_z(angles.z));
	}

	Matrix4 translate(Vector4 displacements)
	{
		Matrix4 to_return;
		to_return.Identity();

		to_return.m[0][3] = displacements.x;
		to_return.m[1][3] = displacements.y;
		to_return.m[2][3] = displacements.z;

		return(to_return);
	}

    Matrix4 perspective(float focus)
	{
		Matrix4 to_return;
		to_return.Zero();

		to_return.m[0][0] = focus;
		to_return.m[1][1] = focus;
		to_return.m[2][2] = focus;

		to_return.m[3][2] = 1.0f;

		return(to_return);
	}


#if 0
    Matrix4 perspective(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 to_return;
		to_return.Zero();

		to_return.m[0][0] = 2.0f*near/(right - left);
		to_return.m[1][1] = 2.0f*near/(top - bottom);
		to_return.m[2][2] = -(far + near) / (far - near);
#if 0
        to_return.m[2][0] = (right + left) / (right - left);
		to_return.m[2][1] = (top + bottom) / (top - bottom);
		to_return.m[2][3] = -1.0f;
        to_return.m[3][2] = -(2.0f * far * near) / (far - near);
#else
		to_return.m[0][2] = (right + left) / (right - left);
		to_return.m[1][2] = (top + bottom) / (top - bottom);
        to_return.m[3][2] = -1.0f;
        to_return.m[2][3] = -(2.0f * far * near) / (far - near);
#endif
		
#endif
	Matrix4 perspective(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 to_return;
		to_return.Zero();

		to_return.m[0][0] = 2.0f*near/(right - left);
		to_return.m[1][1] = 2.0f*near/(top - bottom);
		to_return.m[2][2] = -(far + near) / (far - near);
#if 0
        to_return.m[2][0] = (right + left) / (right - left);
		to_return.m[2][1] = (top + bottom) / (top - bottom);
		to_return.m[2][3] = -1.0f;
        to_return.m[3][2] = -(2.0f * far * near) / (far - near);
#else
		//to_return.m[0][2] = (right + left) / (right - left);
		//to_return.m[1][2] = (top + bottom) / (top - bottom);
        to_return.m[3][2] = -1.0f;
        to_return.m[2][3] = -(2.0f * far * near) / (far - near);
#endif
		return(to_return);
	}

    Matrix4 ortho(float focus)
    {
        Matrix4 to_return;
        to_return.Zero();

        to_return.m[0][0] = focus;
        to_return.m[1][1] = -focus;
        to_return.m[3][3] = 1.0f;
        to_return.m[3][2] = -1.0f;

        return(to_return);
    }
}

