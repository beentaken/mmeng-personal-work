#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector4.h"
#include "Point4.h"
#include "Matrix4.h"

class Camera
{
    public:
        Camera& setPosition(float x, float y, float z);
        Camera& setAngle(float x, float y, float z);
        
        Camera& lookAt(float x, float y, float z);

        Matrix4 getTransformation() const;

    private:
        Vector4 myPosition;
        Vector4 myDirection;

        Matrix4 myCameraMat;
};

#endif // CAMERA_H

