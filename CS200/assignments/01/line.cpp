#include "line.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

namespace
{
	int Round(float input)
	{
		return(static_cast<int>(input + 0.5f));
	}
	
	template<bool MoreHorizontal>
	void DrawLine(const int& start_x, const int& start_y, const int& end_x, const int& end_y);
	
	template<>
	void DrawLine<true>(const int& start_x, const int& start_y, const int& end_x, const int& end_y)
	{
		float slope = static_cast<float>((end_y - start_y)) / (end_x - start_x);
		float current_y = start_y;
		
		for (int current_x = start_x; current_x <= end_x; ++current_x)
		{
			FrameBuffer::SetPixel(current_x, Round(current_y), 0, 0, 0);
			current_y += slope;
		}
	}
	
	template<>
	void DrawLine<false>(const int& start_x, const int& start_y, const int& end_x, const int& end_y)
	{
		float inv_slope = static_cast<float>((end_x - start_x)) / (end_y - start_y);
		float current_x = start_x;
		
		for (int current_y = start_y; current_y <= end_y; ++current_y)
		{
			FrameBuffer::SetPixel(Round(current_x), current_y, 0, 0, 0);
			current_x += inv_slope;
		}
	}
}

Line::Line()
:myStart(), myEnd()
{
}

Line::Line(const Mat3& first, const Mat3& second)
:myStart(first), myEnd(second)
{
//    std::cerr << "Constructing line: " << myStart(0, 0) << ' ' << myStart(1, 1) << ' ' << myEnd(0, 0) << ' ' << myEnd(1, 1) << std::endl;
}

Line::~Line()
{
}

void Line::draw(const Matrix<3, 3, float>& toViewport)
{
    // Doing viewport conversion manually for now.
    // TODO: Make the matrix multiplication right.
//    std::cerr << this << ": ";
	int start_x = static_cast<float>(myStart(0, 0)) * toViewport(0, 0) - toViewport(0, 2);
	int start_y = static_cast<float>(myStart(1, 1)) * toViewport(1, 1) - toViewport(1, 2);
	
	int end_x = static_cast<float>(myEnd(0, 0)) * toViewport(0, 0) - toViewport(0, 2);
	int end_y = static_cast<float>(myEnd(1, 1)) * toViewport(1, 1) - toViewport(1, 2);
	bool more_horizontal = abs(end_x - start_x) > abs(end_y - start_y);

//    std::cerr << start_x << ' ' << start_y << ' ' << end_x << ' ' << end_y << ' ' << std::endl;
	
	// Make sure the start point is always "lower" on the iterating factor than the end.
	if (more_horizontal)
	{		
		if (end_x < start_x) // Bah, wrong order, swap!
		{
			std::swap(start_x, end_x);
			std::swap(start_y, end_y);
		}
		
		DrawLine<true>(start_x, start_y, end_x, end_y);
	}
	else
	{		
		if (end_y < start_y) // Bah, wrong order, swap!
		{
			std::swap(start_x, end_x);
			std::swap(start_y, end_y);
		}
		
		DrawLine<false>(start_x, start_y, end_x, end_y);
	}
}
