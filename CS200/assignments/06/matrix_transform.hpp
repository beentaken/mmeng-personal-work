#ifndef MATRIX_TRANSFORM_H
#define MATRIX_TRANSFORM_H

#include "matrix.hpp"

namespace mat3t
{
    Mat3 translate(int x, int y);

    Mat3 rotate(float angle);

    Mat3 scale(float x, float y);
}

#endif // MATRIX_TRANSFORM_H

