#pragma once
#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "Vector4.h"
#include "Matrix4.h"

namespace mat4
{
    Matrix4 scale(Vector4 scale_factors);

	Matrix4 rotate_x(float angle);
	Matrix4 rotate_y(float angle);
	Matrix4 rotate_z(float angle);

	Matrix4 rotate(Vector4 angles);

	Matrix4 translate(Vector4 displacements);

    Matrix4 rotate(float angle, Vector4 axis);

    Matrix4 perspective(float focus);
    Matrix4 perspective(float left, float right, float bottom, float top, float near, float far);
}

#endif // TRANSFORMATIONS_H

