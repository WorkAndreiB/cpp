#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<int>& vec)
{
    for (const auto& el : vec)
    {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

// possible memory leak if p is NOT explicitly deleted
int* f()
{
    int* p = new int{20};
    return p;
}

void print(std::string& str)
{
    str += "!";
    std::cout << str << "\n";
}

auto greeter(const std::string& salutation)
{
    return [salutation](const std::string& name) { return salutation + " " + name; };
}

// variadic templeate arg
template <typename... Args>
void f(Args... args)
{
    std::cout << "Call with " << sizeof...(args) << " args\n";
}

template <typename T>
T add(T x)
{
    std::cout << "add(T x)\n";
    return x;
}

template <typename T, typename... Args>
T add(T x, Args... args)
{
    std::cout << "add(T x, Args... args)\n";

    return x + add(args...);
}

template <>
std::string add<std::string>(std::string x)
{
    std::cout << "add<string>(T x)\n";
    return x + "!";
}

int main()
{
    auto add_new_line = []() { std::cout << "\n\n"; };
    std::cout << "Salut modern cpp\n";

    std::cout << "Initializer list vector initialization\n";
    print(std::vector<int>{10, 20});
    std::cout << "Fill constructor vector initialization\n";
    print(std::vector<int>(10, 20));
    add_new_line();

    // testing conversion from const to non const.
    std::cout << "Convert from const string for string\n";
    const std::string msg{"Hello World"};
    print(const_cast<std::string&>(msg));
    add_new_line();

    int* p = f();
    if (p)
    {
        std::cout << "*p= " << *p << "\n";
        std::cout << "delete p... \n";
        // WARNING: Dereferencing a pointer after it has been deleted causes undefined behavior!
        delete p;
    }
    add_new_line();

    // testing greeter
    auto greet = greeter("Hello");

    std::cout << greet("Gigi") << "\n";

    std::cout << greeter("Hello")("Mada") << "\n";

    add_new_line();

    // testing variadic templates
    f(4.0F, "ana are mere", 2U);
    f(4.0F);

    auto sum = add(1.6, 5.05, 7.8, 20);
    std::cout << "sum = " << sum << "\n";

    auto result = add(std::string{"unu "}, std::string{"doi "}, std::string{"cinci "});
    std::cout << "result = " << result << "\n";

    return 0;
}