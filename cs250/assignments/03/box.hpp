#pragma once
#ifndef BOX_H
#define BOX_H

#include <memory>
#include <vector>
#include "triangle.hpp"

#include "Vector4.h"
#include "Matrix4.h"

class BoxGeometryComponent
{
    public:
        BoxGeometryComponent(const std::vector<Triangle> &triangles);

        BoxGeometryComponent& attachComponent(std::shared_ptr<BoxGeometryComponent> component);

        void draw(Matrix4 transformation);

		BoxGeometryComponent& addRotation(float angle_x, float angle_y, float angle_z);
		BoxGeometryComponent& addTranslation(float x, float y, float z);
		BoxGeometryComponent& addScale(float x, float y, float z);
        BoxGeometryComponent& move(float x, float y, float z);
        BoxGeometryComponent& turn(float x, float y, float z);

        Vector4 getPosition() const;

    private:
        std::vector<std::shared_ptr<BoxGeometryComponent>> myComponents;
        std::vector<Triangle> myTriangles;

        Vector4 myScale;
        Vector4 myRotation;
        Vector4 myTranslation;
        Vector4 myMove;
        Vector4 myTurn;
};

#endif // BOX_H

