#include "point.hpp"

#include <iostream>

Point::Point(int x, int y) : x(x), y(y)
{
    std::cout << "Point(x,y)\n";
}

Point::Point(Point&& p) : x(p.x), y(p.y)
{
    std::cout << "Point(Point&& p)\n";
}

Point& Point::operator=(Point&& point)
{
    std::cout << "operator=\n";
    if (this != &point)
    {
        x = point.x;
        y = point.y;
    }
    return *this;
}

Point::~Point()
{
    std::cout << "~Point()\n";
}

void Point::print()
{
    std::cout << x << " " << y << "\n";
}