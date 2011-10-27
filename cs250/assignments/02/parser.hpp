#pragma once
#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Point4.h"
#include "Vector4.h"
#include "triangle.hpp"

class InputParser
{
	public:
		InputParser(const std::string &filename);

		void parse();

        const std::vector<Point4>& getVertices() const
        {
            return(myVertices);
        }
        const std::vector<Vector4>& getFaceColors() const
        {
            return(myFaceColors);
        }

        const std::vector<Vector4>& getFaces() const
        {
            return(myTriangleCorners);
        }
        const std::vector<Triangle>& getTriangles() const
        {
            return(myTriangles);
        }
        const std::vector<Vector4>& getTexCoords() const
        {
            return(myTexCoords);
        }

	private:

		std::string myFilename;
	    std::unordered_map<std::string, std::string> camera_data;
        std::vector<Point4> myVertices;
        std::vector<Vector4> myTriangleCorners;
        std::vector<Triangle> myTriangles;
        std::vector<Vector4> myFaceColors;
        std::vector<Vector4> myTexCoords;
};

#endif // INPUT_PARSER_H

