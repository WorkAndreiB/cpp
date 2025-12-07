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

// possible memory leak if p is explicitly deleted
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
    std::cout << "*p= " << *p << "\n";
    if (p)
    {
        std::cout << "delete p... \n";
        // WARNING: Dereferencing a pointer after it has been deleted causes undefined behavior!
        delete p;
    }
    add_new_line();

    auto greet = greeter("Hello");

    std::cout << greet("Gigi") << "\n";

    std::cout << greeter("Hello")("Mada") << "\n";

    return 0;
}