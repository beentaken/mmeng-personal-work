#include "camera.hpp"

#include "transformations.hpp"

Camera& Camera::setPosition(float x, float y, float z)
{
    myPosition.x = x;
    myPosition.y = y;
    myPosition.z = z;

    return(*this);
}

Camera& Camera::setAngle(float x, float y, float z)
{
    myDirection.x = x;
    myDirection.y = y;
    myDirection.z = z;

    return(*this);
}

Camera& Camera::lookAt(float x, float y, float z)
{
    Vector4 z_axis = Vector4(x, y, z) - myPosition;
    z_axis.Normalize();

    Vector4 x_axis = Vector4(0, 1, 0).Cross(z_axis);
    x_axis.Normalize();
    
    Vector4 y_axis = z_axis.Cross(x_axis);

    myCameraMat.Zero();

    myCameraMat.m[0][0] = x_axis.x;
    myCameraMat.m[0][1] = x_axis.y;
    myCameraMat.m[0][2] = x_axis.z;

    myCameraMat.m[1][0] = y_axis.x;
    myCameraMat.m[1][1] = y_axis.y;
    myCameraMat.m[1][2] = y_axis.z;

    myCameraMat.m[2][0] = z_axis.x;
    myCameraMat.m[2][1] = z_axis.y;
    myCameraMat.m[2][2] = z_axis.z;

    myCameraMat.m[3][3] = 1.0f;

    return(*this);
}

Matrix4 Camera::getTransformation() const
{
    return(myCameraMat);
}

