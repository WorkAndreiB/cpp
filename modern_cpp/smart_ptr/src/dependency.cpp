#include "dependency.hpp"

#include <iostream>

B::~B()
{
    std::cout << "~B()\n";
}

void B::setA(const std::shared_ptr<A>& other)
{
    a = other;
}

A::~A()
{
    std::cout << "~A()\n";
}

A::A(const std::shared_ptr<B> other)
{
    std::cout << "A(shared_ptr<B>)\n";
    b = other;
}
