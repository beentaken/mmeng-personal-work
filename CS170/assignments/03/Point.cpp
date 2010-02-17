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

Point::Point() : x_(0.0), y_(0.0)
{
}

Point::Point(const double x, const double y) : x_(x), y_(y)
{
}

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

double Point::operator-(const Point &rhs) const
{
	return(std::sqrt(std::abs(square(rhs.x_ - x_) + square(rhs.y_ - y_))));
}

Point Point::operator^(const Point &rhs) const
{
	return(Point((x_ + rhs.x_) / 2, (y_ + rhs.y_) / 2));
}

Point& Point::operator+=(const Point &rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;

	return(*this);
}

Point& Point::operator+=(const double &rhs)
{
	x_ += rhs;
	y_ += rhs;

	return(*this);
}

Point Point::operator-(const double &rhs) const
{
	return(Point(x_ - rhs, y_ - rhs));
}

Point& Point::operator++()
{
	++x_;
	++y_;

	return(*this);
}

Point Point::operator++(int)
{
	Point temp(x_, y_);

	++x_;
	++y_;

	return(temp);
}

Point& Point::operator--()
{
	--x_;
	--y_;

	return(*this);
}

Point Point::operator--(int)
{
	Point temp(x_, y_);

	--x_;
	--y_;

	return(temp);
}

Point Point::operator-() const
{
	return(Point(-x_, -y_));
}

Point Point::operator+(const Point &rhs) const
{
	return(Point(x_ + rhs.x_, y_ + rhs.y_));
}

Point Point::operator*(const double &rhs) const
{
	return(Point(x_ * rhs, y_ * rhs));
}

///////////////////////////////////////////////////////////////////////////////
// 2 friend functions (operators)

std::ostream& operator<<(std::ostream &lhs, const Point &rhs)
{
	lhs << '(' << rhs.x_ << ", " << rhs.y_ << ')';

	return(lhs);
}

std::istream& operator>>(std::istream &lhs, Point &rhs)
{
	lhs >> rhs.x_ >> rhs.y_;

	return(lhs);
}

///////////////////////////////////////////////////////////////////////////////
// 2 non-members, non-friends (operators)

Point operator+(const double &lhs, const Point &rhs)
{
	return(rhs + Point(lhs, lhs));
}

Point operator+(const Point &lhs, const double &rhs)
{
	return(rhs + lhs);
}

Point operator*(const double &lhs, const Point &rhs)
{
	return(rhs * lhs);
}

} // namespace CS170



