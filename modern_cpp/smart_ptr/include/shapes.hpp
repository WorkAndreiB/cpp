#ifndef MODERN_CPP_SMART_PTR_SHAPES_HPP
#define MODERN_CPP_SMART_PTR_SHAPES_HPP

#include <iostream>

class Shape
{
   public:
    virtual void print()
    {
        std::cout << "Shape()\n";
    }
};

class Rectangle : public Shape
{
   public:
    void print() override
    {
        std::cout << "Recatangle()\n";
    }
};

class Circle : public Shape
{
   public:
    void print() override
    {
        std::cout << "Circle()\n";
    }
};

#endif  // MODERN_CPP_SMART_PTR_SHAPES_HPP