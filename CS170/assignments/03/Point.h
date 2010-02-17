////////////////////////////////////////////////////////////////////////////////
#ifndef POINT_H
#define POINT_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // istream, ostream

namespace CS170
{
  class Point
  {
    public:
        // Constructors (2)
	Point();
	Point(const double x, const double y);

        // Overloaded operators (14 member functions)
	Point operator%(const double &rhs) const;
	double operator-(const Point &rhs) const;
	Point operator^(const Point &rhs) const;
	Point& operator+=(const Point &rhs);
	Point& operator+=(const double &rhs);
	Point operator-(const double &rhs) const;
	Point& operator++();
	Point operator++(int); //Postdec
	Point& operator--();
	Point operator--(int); //Postdec
	Point operator-() const;
	Point operator+(const Point& rhs) const;
	Point operator*(const double& rhs) const;
        
        // Overloaded operators (2 friend functions)
	friend std::ostream& operator<<(std::ostream &lhs, const Point &rhs);
	friend std::istream& operator>>(std::istream &lhs, Point &rhs);
        
    private:
      double x_; // The x-coordinate of a Point
      double y_; // The y-coordinate of a Point

        // Helper functions
      double DegreesToRadians(double degrees) const;
      double RadiansToDegrees(double radians) const;
  };
  
    // Overloaded operators (2 non-member, non-friend functions)
    Point operator+(const double &lhs, const Point &rhs);
    Point operator+(const Point &lhs, const double &rhs);
    Point operator*(const double &lhs, const Point &rhs);
    
} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////

