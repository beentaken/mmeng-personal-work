#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace
{
    void SetTriangleColors(Triangle& to_set, Vector4 color)
    {
        to_set.c0 = to_set.c1 = to_set.c2 = color;
    }

    void SetTriangleTexCoord(Triangle& to_set, Vector4 tex_coord)
    {
        to_set.t0 = tex_coord;
    }

    struct TriangleVectorCreator
    {
        std::vector<Triangle>& myTriangles;
        std::vector<Point4>& myVertices;

        TriangleVectorCreator(std::vector<Triangle>& new_vector, std::vector<Point4>& new_vertex_list)
            :myTriangles(new_vector), myVertices(new_vertex_list)
        {
        }

        void operator()(Vector4 vertices)
        {
            myTriangles.push_back(Triangle(myVertices[vertices.x], myVertices[vertices.y], myVertices[vertices.z]));
        }
    };

	void PrintCameraData(const std::unordered_map<std::string, std::string>& data)
	{
		std::cout << "Camera data imported:" << std::endl;
		std::cout << "\tLeft: " << data.at("left") << std::endl;
		std::cout << "\tRight: " << data.at("right") << std::endl;
		std::cout << "\tTop: " << data.at("top") << std::endl;
		std::cout << "\tBottom: " << data.at("bottom") << std::endl;
		std::cout << "\tFocal: " << data.at("focal") << std::endl;
		std::cout << "\tNear: " << data.at("near") << std::endl;
		std::cout << "\tFar: " << data.at("far") << std::endl;
	}

    void PrintTokens(const std::string& input, char seperator)
    {
        std::stringstream ss(input);
        std::string token;
        while(std::getline(ss, token, seperator))
        {
            std::cout << token << std::endl;
        }
    }

    template<typename Contained, unsigned components = 4>
    void ParseVector(std::vector<Contained>& output, const std::vector<std::string>& input)
    {
        static_assert(components >=2 && components <= 4, "Parser only deals with "
                "inputs with 2 to 4 components.");

        for (auto it = input.begin(); it != input.end(); ++it)
        {
            std::stringstream ss(*it);
            std::string token;
            while(std::getline(ss, token, ','))
            {
                std::stringstream string_to_floater(token);
                float x, y, z, w;
                string_to_floater >> x;

                std::getline(ss, token, ',');
                string_to_floater.str(token);
                string_to_floater >> y;

                if (components >= 3)
                {
                    std::getline(ss, token, ',');
                    string_to_floater.str(token);
                    string_to_floater >> z;
                }
                else
                {
                    z = 0.0f;
                }

                if (components == 4)
                {
                    std::getline(ss, token, ',');
                    string_to_floater.str(token);
                    string_to_floater >> w;
                }
                else
                {
                    w = 0.0f;
                }

                output.push_back(Contained(x, y, z, w));
            }
        }
    }
}

InputParser::InputParser(const std::string &filename)
	:myFilename(filename), camera_data(), myVertices(), myTriangleCorners(),
    myTriangles(), myFaceColors(), myTexCoords()
{
}

void InputParser::parse()
{
	std::fstream input(myFilename, std::ios::in);

	std::vector<std::string> buffer;

	if (input.is_open())
	{
		std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(buffer));
	}
    else
    {
        throw(std::runtime_error("Couldn't open file."));
    }

	// Get camera data.
	auto it = buffer.begin();

    if (it == buffer.end())
    {
        // What the hell?
        throw(std::runtime_error("Buffer is baaad."));
    }

	while( *it != "}")
	{
		if (*it == "=")
		{
			camera_data[*(it - 1)] = *(it + 1);
		}
		++it;
	}
	++it;

	PrintCameraData(camera_data);

	// Get vertices.

	std::vector<std::string> vertices;

	while( *it != "}")
	{
		if (*it == "=")
		{
			it += 2;
			while (*it != "}")
			{
				vertices.push_back(*it);
				++it;
			}
		}
		else
		{
			++it;
		}
	}
	++it;

    ParseVector<Point4, 4>(myVertices, vertices);

	std::vector<std::string> faces;

	while( *it != "}")
	{
		if (*it == "=")
		{
			it += 2;
			while (*it != "}")
			{
				faces.push_back(*it);
				++it;
			}
		}
		else
		{
			++it;
		}
	}
	++it;

    ParseVector<Vector4, 3>(myTriangleCorners, faces);

	std::vector<std::string> face_colors;

	while( *it != "}")
	{
		if (*it == "{")
		{
			++it;
			while (*it != "}")
			{
				face_colors.push_back(*it);
				++it;
			}
		}
		else
		{
			++it;
		}
	}
    ParseVector<Vector4, 3>(myFaceColors, face_colors);
	++it;
	std::vector<std::string> texture_coordinates;

	while( *it != "}")
	{
		if (*it == "{")
		{
			++it;
			while (*it != "}")
			{
				texture_coordinates.push_back(*it);
				++it;
			}
		}
		else
		{
			++it;
		}
	}

    ParseVector<Vector4, 2>(myTexCoords, texture_coordinates);

    // All right, now to create triangles.

    TriangleVectorCreator triangler(myTriangles, myVertices);
    std::for_each(myTriangleCorners.begin(), myTriangleCorners.end(), triangler);

    for (unsigned i = 0; i < myTriangles.size(); ++i)
    {
        SetTriangleColors(myTriangles[i], myFaceColors[i]);
    }
}

