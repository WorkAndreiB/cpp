#include <array>
#include <iostream>
#include <numeric>

// recursive
constexpr int add(const std::array<int, 10>& numbers, std::array<int, 10>::const_iterator it)
{
    if (it == numbers.cend())
    {
        return 0;
    }
    return *it + add(numbers, std::next(it));
}

// variadic template
template <typename T>
T add(T el)
{
    return el;
}
template <typename T, typename... Args>
T add(T el, Args... args)
{
    return el + add(args...);
}

// parameter pack
template <int... Ns>
int add()
{
    if (sizeof...(Ns) == 0)
    {
        return 0;
    }
    return (Ns + ...);
}

// recursive parameter pack
template <int first, int... Rest>
constexpr int add_recursive()
{
    if constexpr (sizeof...(Rest) == 0)
    {
        return first;
    }
    else
    {
        return first + add_recursive<Rest...>();
    }
}

// implement different ways of computing the sum of some numbers
int main()
{
    constexpr std::array<int, 10> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Sum v1: clasic c-style for loop
    int sum = 0;
    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        sum += numbers.at(i);
    }
    std::cout << "c-style sum = " << sum << "\n";

    // Sum v2: range based loop
    sum = 0;
    for (auto number : numbers)
    {
        sum += number;
    }
    std::cout << "range based loop sum = " << sum << "\n";

    // Sum v3: std::algorithm
    sum = 0;
    sum = std::accumulate(numbers.cbegin(), numbers.cend(), 0);
    std::cout << "std::accumulate sum = " << sum << "\n";

    // Sum v4: recurssive
    sum = 0;
    sum = add(numbers, numbers.cbegin());
    std::cout << "recursive sum = " << sum << "\n";

    // Sum v5: variadic template
    sum = 0;
    sum = add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    std::cout << "variadic template sum = " << sum << "\n";

    // Sum v6: pararmeter pack
    sum = 0;
    sum = add<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>();
    std::cout << "parameter pack sum = " << sum << "\n";

    // Sum v7: recursive pararmeter pack
    sum = 0;
    sum = add_recursive<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>();
    std::cout << "recursive parameter pack sum = " << sum << "\n";

    return 0;
}