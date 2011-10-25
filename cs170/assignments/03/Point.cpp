/******************************************************************************/
/*!
\file   Point.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment #3
\date   2/17/2010
\brief
	This file contains the implementations for the constructors and the
	overloaded operators dealing with the Point class.

  Hours spent on this assignment: 1

  Specific portions that gave you the most trouble: 
  
  Just debugging.

*/
/******************************************************************************/

#include "Point.h"  // Point members
#include <cmath>    // sqrt, atan, sin, cos, abs

namespace
{
	// Squares the number given to it.
	double square(const double &toSquare)
	{
		return(toSquare * toSquare);
	}
}

namespace CS170
{

const double PI = 3.1415926535897;
const double EPSILON = 0.00001;

///////////////////////////////////////////////////////////////////////////////
// private member functions 
double Point::DegreesToRadians(double degrees) const
{
  return (degrees * PI / 180.0);
}

double Point::RadiansToDegrees(double radians) const
{
  return (radians * 180.0 / PI);
}


///////////////////////////////////////////////////////////////////////////////
// 16 public member functions (2 constructors, 14 operators) 

/*****************************************************************************/
/*!
\brief
	Constructs a point with the default values of 0, 0.
*/
/*****************************************************************************/
Point::Point() : x_(0.0), y_(0.0)
{
}

/*****************************************************************************/
/*!
\brief
	Constructs a point at the given coordinates.

\param x
	The X coordinate.

\param y
	The Y coordinate.
*/
/*****************************************************************************/
Point::Point(const double x, const double y) : x_(x), y_(y)
{
}

// Rotates the point by the given number of degrees.
Point Point::operator%(const double &rhs) const
{
	double in_radians(DegreesToRadians(rhs));

	// The x_value of the new Point.
	double new_x(x_ * std::cos(in_radians) - y_ * std::sin(in_radians));
	// The y_value of the new Point.
	double new_y(x_ * std::sin(in_radians) + y_ * std::cos(in_radians));

	if (std::abs(new_x) < EPSILON)
	{
		new_x = 0.0;
	}
	if (std::abs(new_y) < EPSILON)
	{
		new_y = 0.0;
	}

	return(Point(new_x, new_y));
}

// Finds the distance between two points.
double Point::operator-(const Point &rhs) const
{
	return(std::sqrt(std::abs(square(rhs.x_ - x_) + square(rhs.y_ - y_))));
}

// Finds the midpoint of two points.
Point Point::operator^(const Point &rhs) const
{
	return(Point((x_ + rhs.x_) / 2, (y_ + rhs.y_) / 2));
}

// Translates a point by the value of a second point.
Point& Point::operator+=(const Point &rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;

	return(*this);
}

// Translates the x and y coordinates of a point by the value.
Point& Point::operator+=(const double &rhs)
{
	x_ += rhs;
	y_ += rhs;

	return(*this);
}

// Translates a point by the negative of the provided value.
Point Point::operator-(const double &rhs) const
{
	return(Point(x_ - rhs, y_ - rhs));
}

// Pre-increments the X and Y coordinates of the point.
Point& Point::operator++()
{
	++x_;
	++y_;

	return(*this);
}

// Post-increments the X and Y coordinates of the point.
Point Point::operator++(int)
{
	Point temp(x_, y_);

	++x_;
	++y_;

	return(temp);
}

// Pre-decrements the X and Y values of the point.
Point& Point::operator--()
{
	--x_;
	--y_;

	return(*this);
}

// Post-decrements the X and Y values of the point.
Point Point::operator--(int)
{
	Point temp(x_, y_);

	--x_;
	--y_;

	return(temp);
}

// Multiples the X and Y values of the point by -1.
Point Point::operator-() const
{
	return(Point(-x_, -y_));
}

// Translates a point by the value of the second Point.
Point Point::operator+(const Point &rhs) const
{
	return(Point(x_ + rhs.x_, y_ + rhs.y_));
}

// Translates a point by the value of the provided constant.
Point Point::operator*(const double &rhs) const
{
	return(Point(x_ * rhs, y_ * rhs));
}

///////////////////////////////////////////////////////////////////////////////
// 2 friend functions (operators)

// Inserts the point into an ostream in the "(X, Y)" format.
std::ostream& operator<<(std::ostream &lhs, const Point &rhs)
{
	lhs << '(' << rhs.x_ << ", " << rhs.y_ << ')';

	return(lhs);
}

// Reads two values into the point.
std::istream& operator>>(std::istream &lhs, Point &rhs)
{
	lhs >> rhs.x_ >> rhs.y_;

	return(lhs);
}

///////////////////////////////////////////////////////////////////////////////
// 2 non-members, non-friends (operators)

// Adds a double and a point.
Point operator+(const double &lhs, const Point &rhs)
{
	return(rhs + Point(lhs, lhs));
}

// Adds a point and a double.
Point operator+(const Point &lhs, const double &rhs)
{
	return(rhs + lhs);
}

// Scales a point by the double provided.
Point operator*(const double &lhs, const Point &rhs)
{
	return(rhs * lhs);
}

} // namespace CS170



