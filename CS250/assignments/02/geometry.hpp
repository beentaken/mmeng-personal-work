#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory> // shared_ptr
#include <vector>

class Matrix4;

class GeometryComponent
{
    public:
        typedef std::vector<std::shared_ptr<GeometryComponent>> GeometryComponentArray;
        GeometryComponent();

        virtual void draw(Matrix4 transformation);

    private:
        GeometryComponentArray myComponents;
};

#endif // GEOMETRY_H

