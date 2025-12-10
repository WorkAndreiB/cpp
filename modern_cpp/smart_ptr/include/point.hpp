#ifndef MODERN_CPP_SMART_PTR_POINT_HPP
#define MODERN_CPP_SMART_PTR_POINT_HPP

class Point
{
    int x;
    int y;

   public:
    Point() = default;
    Point(int x, int y);
    Point(Point&& p);
    Point& operator=(Point&& point);
    Point(const Point& point) = delete;
    Point& operator=(Point& point) = delete;
    ~Point();

    void print();
};

#endif  // MODERN_CPP_SMART_PTR_POINT_HPP