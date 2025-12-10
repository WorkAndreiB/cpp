#ifndef MODERN_CPP_SMART_PTR_DEPENDENCY_HPP
#define MODERN_CPP_SMART_PTR_DEPENDENCY_HPP

#include <iostream>
#include <memory>

class A;

class B
{
    std::shared_ptr<A> a;

   public:
    ~B();
    void setA(const std::shared_ptr<A>& other);
};

class A
{
    std::weak_ptr<B> b;
    // std::shared_ptr<B> b;

   public:
    ~A();
    A(const std::shared_ptr<B> other);
};

#endif  // MODERN_CPP_SMART_PTR_DEPENDENCY_HPP