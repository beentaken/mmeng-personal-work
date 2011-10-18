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
        BoxGeometryComponent(std::vector<Triangle> &triangles);

        void attachComponent(std::shared_ptr<BoxGeometryComponent> component);

        void draw(Matrix4 transformation);

		void addRotation(float angle);
		void addTranslation(float x, float y, float z);
		void addScale(float x, float y, float z);

    private:
        std::vector<std::shared_ptr<BoxGeometryComponent>> myComponents;
        std::vector<Triangle> myTriangles;

        Vector4 myScale;
        Vector4 myRotation;
        Vector4 myTranslation;
};

#endif // BOX_H

