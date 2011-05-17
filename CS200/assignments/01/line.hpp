#ifndef LINE_H
#define LINE_H

#include "Utilities.h"
#include "matrix.hpp"

class Line
{
	public:
		Line();
		Line(const Mat3 &first, const Mat3 &second);
		~Line();
		
		void draw();

	private:
		Mat3 myStart;
		Mat3 myEnd;
};

#endif // LINE_H
