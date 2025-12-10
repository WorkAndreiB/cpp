#include <iostream>
#include <memory>
#include <vector>

#include "dependency.hpp"
#include "point.hpp"
#include "shapes.hpp"

void print(std::unique_ptr<Point> point)
{
    point->print();
}

std::unique_ptr<Point> create_pointer(int x, int y)
{
    return std::make_unique<Point>(Point{x, y});
}

int main()
{
    auto p = std::make_unique<Point>(Point{10, 20});
    p->print();
    print(std::move(p));

    if (p == nullptr)
    {
        std::cout << "p ownership has been moved when calling print(std::move(p)); p is now null\n";
    }

    // return unique_ptr from function
    auto ptr = create_pointer(2, 4);
    ptr->print();

    auto ptr2 = std::move(ptr);
    ptr2->print();
    if (ptr == nullptr)
    {
        std::cout << "ptr ownership has been moved when calling std::move(ptr); ptr is now null\n";
    }

    // polymorphism with unique_ptr
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Shape>());
    shapes.push_back(std::make_unique<Rectangle>());
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Rectangle>(Rectangle{}));
    shapes.push_back(std::make_unique<Shape>(Rectangle{}));

    for (const auto& shape : shapes)
    {
        shape->print();
    }

    // create unique_ptr with custom deleter
    {
        const auto custom_deleter = [](Point* p)
        {
            p->print();
            std::cout << "Custom unique ptr deleter\n";
        };

        std::unique_ptr<Point, decltype(custom_deleter)> custom_ptr(new Point(100, 200),
                                                                    custom_deleter);

        custom_ptr->print();
    }

    // test cyclic dependency shared_ptr vs weak_ptr
    {
        auto pb = std::make_shared<B>();
        auto pa = std::make_shared<A>(pb);
        pb->setA(pa);
    }

    return 0;
}