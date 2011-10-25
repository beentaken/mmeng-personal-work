/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: line.cpp
Purpose: Implementation of functions needed to draw arbitrary lines in a viewport.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

#include "line.hpp"

#include "Utilities.h"

#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace
{
	int Round(float input)
	{
		return(static_cast<int>(input + 0.5f));
	}
	
	template<bool MoreHorizontal>
	void DrawLine(const int& start_x, const int& start_y, const int& end_x, const int& end_y, Color color);
	
	template<>
	void DrawLine<true>(const int& start_x, const int& start_y, const int& end_x, const int& end_y, Color color)
	{
		float slope = static_cast<float>((end_y - start_y)) / static_cast<float>((end_x - start_x));
		float current_y = static_cast<float>(start_y);
		
		for (int current_x = start_x; current_x <= end_x; ++current_x)
		{
			FrameBuffer::SetPixel(current_x, Round(current_y), color.r, color.g, color.b);
			current_y += slope;
		}
	}
	
	template<>
	void DrawLine<false>(const int& start_x, const int& start_y, const int& end_x, const int& end_y, Color color)
	{
		float inv_slope = static_cast<float>((end_x - start_x)) / static_cast<float>((end_y - start_y));
		float current_x = static_cast<float>(start_x);
		
		for (int current_y = start_y; current_y <= end_y; ++current_y)
		{
			FrameBuffer::SetPixel(Round(current_x), current_y, color.r, color.g, color.b);
			current_x += inv_slope;
		}
	}
}

Line::Line()
:myStart(), myEnd()
{
    myColor.r = 0;
    myColor.g = 0;
    myColor.b = 0;
}

Line::Line(const Matrix<3, 3, float>& first, const Matrix<3, 3, float>& second, const Color& color)
:myStart(first), myEnd(second), myColor(color)
{
}

Line::~Line()
{
}

void Line::setColor(unsigned char r, unsigned char g, unsigned char b)
{
    myColor.r = r;
    myColor.g = g;
    myColor.b = b;
}

void Line::draw(const Matrix<3, 3, float>& toViewport)
{
    Matrix<3, 3, float> start(toViewport * myStart), end(toViewport * myEnd);

    // Accumulating because our points are only stored in matrices right now, not
    // vectors. TODO: generalize matrix library to handle one-dimensional matrices
    // as well.
    int start_x = Round(std::accumulate(start.row_begin(0), start.row_end(0), 0.0f));
    int start_y = Round(std::accumulate(start.row_begin(1), start.row_end(1), 0.0f));

    int end_x = Round(std::accumulate(end.row_begin(0), end.row_end(0), 0.0f));
    int end_y = Round(std::accumulate(end.row_begin(1), end.row_end(1), 0.0f));

	bool more_horizontal = abs(end_x - start_x) > abs(end_y - start_y);

	// Make sure the start point is always "lower" on the iterating factor than the end.
	if (more_horizontal)
	{		
		if (end_x < start_x) // Bah, wrong order, swap!
		{
			std::swap(start_x, end_x);
			std::swap(start_y, end_y);
		}
		
		DrawLine<true>(start_x, start_y, end_x, end_y, myColor);
	}
	else
	{		
		if (end_y < start_y) // Bah, wrong order, swap!
		{
			std::swap(start_x, end_x);
			std::swap(start_y, end_y);
		}
		
		DrawLine<false>(start_x, start_y, end_x, end_y, myColor);
	}
}
