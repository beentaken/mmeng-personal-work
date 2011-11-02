#include "camera.hpp"

#include "transformations.hpp"
#include <iostream>

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
	// [View]
	// [Up]
	// [Left]
	//std::cout << "My position: " << myPosition.x << ' ' << myPosition.y << ' ' << myPosition.z << std::endl;
    Vector4 z_axis = Vector4(x, y, z) - myPosition;
	//Vector4 z_axis = myPosition - Vector4(x, y, z);
    z_axis.Normalize();

    Vector4 x_axis = Vector4(0, 1, 0).Cross(z_axis);
	//Vector4 x_axis = z_axis.Cross(Vector4(0, 1, 0));
    x_axis.Normalize();
    
    Vector4 y_axis = z_axis.Cross(x_axis);
	//Vector4 y_axis = x_axis.Cross(z_axis);

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

	myCameraMat.m[0][3] = -myPosition.Dot(x_axis);
	myCameraMat.m[1][3] = -myPosition.Dot(y_axis);
	myCameraMat.m[2][3] = -myPosition.Dot(z_axis);

    myCameraMat.m[3][3] = 1.0f;

    return(*this);
}

Matrix4 Camera::getTransformation() const
{
#if 0
	Vector4 inverse_position;
	inverse_position.x = -myPosition.x;
	inverse_position.y = -myPosition.y;
	inverse_position.z = -myPosition.z;

    return(mat4::translate(inverse_position) * myCameraMat);
#else
	return(myCameraMat);
#endif
}

