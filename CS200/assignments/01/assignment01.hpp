#ifndef CS200_ASSIGNMENT_01_H
#define CS200_ASSIGNMENT_01_H

#include "matrix.hpp" // Mat3
#include <vector>
#include "line.hpp"

class Assignment01
{
    public:
        Assignment01();

        void drawScene();

    private:
        const int num_points;
        std::vector<Mat3> points;

        const int num_lines;
        std::vector<Line> lines;

        Matrix<3, 3, float> myCameraToViewport;

        void myCreatePoints();
        const Mat3& myGetPoint(int point);
        void myCreateLines();

        void myCalculateCameraToViewport();

        void test() const;
};

#endif // CS200_ASSIGNMENT_01_H

