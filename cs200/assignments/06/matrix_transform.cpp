#include "matrix_transform.hpp"
#include <cmath>
#include "Utilities.h"

namespace mat3t
{
    Mat3 translate(int x, int y)
    {
        Mat3 to_return(Mat3::Identity());

        to_return(0, 2) = static_cast<float>(x);
        to_return(1, 2) = static_cast<float>(y);

        return(to_return);
    }

    Mat3 rotate(float angle)
    {
        Mat3 to_return(Mat3::Identity());

        angle /= 180.0f/static_cast<float>(PI); // Convert to radians.

        to_return(0, 0) = std::cos(angle);
        to_return(1, 1) = std::cos(angle);
        to_return(0, 1) = -std::sin(angle);
        to_return(1, 0) = std::sin(angle);

        return(to_return);
    }

    Mat3 scale(float x, float y)
    {
        Mat3 to_return(Mat3::Identity());

        to_return(0, 0) = x;
        to_return(1, 1) = y;

        return(to_return);
    }
}

