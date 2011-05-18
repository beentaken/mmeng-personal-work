#include "assignment01.hpp"

Assignment01::Assignment01()
    :num_points(9), points(num_points), num_lines(9), lines(num_lines)
{
    myCreatePoints();
    myCreateLines();

    myCalculateCameraToViewport();

//    test();
}

void Assignment01::drawScene()
{
    for (int i = 0; i < num_lines; ++i)
    {
        lines[i].draw(myCameraToViewport);
    }
}

// Sets up the points stated in the assignment.
void Assignment01::myCreatePoints()
{
    int x_list[] = {-300, -300, -100, -100, 300, 300, 100, 100,  100};
    int y_list[] = { 200, -200, -150,  150,   0, 200, 200,   0, -200};

    for (int i = 0; i < num_points; ++i)
    {
        Mat3 new_point;

        new_point(0,0) = x_list[i];
        new_point(1,1) = y_list[i];

        points[i] = new_point ;
//        std::cerr << "New point added: " << points[i](0, 0) << ' ' << points[i](1, 1) << std::endl;
    }
}

// To make the point indices match up with the assignment ones.
const Mat3& Assignment01::myGetPoint(int point)
{
//    std::cerr << "Getting point: " << points[point - 1](0, 0) << ' ' << points[point - 1](1, 1) << std::endl;
    return(points[point - 1]);
}

void Assignment01::myCreateLines()
{
    int starts[] = {1, 2, 3, 4, 5, 6, 7, 8, 8};
    int ends[] =   {2, 3, 4, 1, 6, 7, 8, 5, 9};
    
    for (int i = 0; i < num_lines; ++i)
    {
//        std::cerr << "Assigning point: " << myGetPoint(starts[i])(0, 0) << ' ' << myGetPoint(starts[i])(1, 1) << std::endl;
        lines[i] = Line(points[starts[i]-1], points[ends[i] - 1]);
    }
}

void Assignment01::myCalculateCameraToViewport()
{
    // Normalize manually while I write a float/int combo matrix system.
    Matrix<3, 3, float> current, temp;

    current(0, 0) = 640.0f / 800;
    current(1, 1) = -480.0f / 600; // Flipped axis.
    current(2, 2) = 1.0f;

//    std::cerr << "Current: " << current(0, 0) << ' ' << current(1, 1) << std::endl;
/*
    temp(0, 0) = 1.0f;
    temp(1, 1) = 1.0f;
    temp(2, 2) = 1.0f;

    temp(0, 2) = -800.0f / 2;
    temp(0, 2) = 600.0f / 2;

    myCameraToViewport = current * temp;
*/
    // For now, just stuff the displacement into the matrix, will do it properly
    // later.
    current(0, 2) = -640.0f / 2;
    current(1, 2) = -480.0f / 2;
    myCameraToViewport = current;
//    std::cerr << "Final: " << myCameraToViewport(0, 0) << ' '
//        << myCameraToViewport(1, 1) << ' '
//        << myCameraToViewport(2, 2) << std::endl;
}

void Assignment01::test() const
{
    std::cout << "Points vector size: " << points.size() << std::endl;
    for (int i = 0; i < num_points; ++i)
    {
        std::cout << "Point " << i << ": " << points[i](0, 0) << ' ' << points[i](1, 1) << std::endl;
    }
}

