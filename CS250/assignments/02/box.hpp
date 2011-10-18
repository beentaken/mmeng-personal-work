#pragma once
#ifndef BOX_H
#define BOX_H

#include "geometry.hpp"
#include "triangle.hpp"

#include "Vector4.h"

class BoxGeometryComponent : public GeometryComponent
{
    public:
        BoxGeometryComponent(std::vector<Triangle> &triangles);

        void draw(Matrix4 transformation);

		void addRotation(float angle);
		void addTranslation(float x, float y, float z);
		void addScale(float x, float y, float z);

    private:
        std::vector<Triangle> myTriangles;

        Vector4 myScale;
        Vector4 myRotation;
        Vector4 myTranslation;
};

#endif // BOX_H

