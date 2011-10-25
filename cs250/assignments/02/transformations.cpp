#include "transformations.hpp"

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
}

