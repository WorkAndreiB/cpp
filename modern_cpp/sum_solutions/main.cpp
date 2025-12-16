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

// fold expression
template <typename... Args>
constexpr auto add_fold_expresion(Args... args)
{
    return (args + ...);
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

    // Sum v6: constexpr fold expression
    // since const_sum and add_fold_expresion are constexpr the expansion and evaluation are done at
    // compile time
    constexpr auto const_sum = add_fold_expresion(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    // template<>
    // int add<int, int, int, int, int, int, int, int, int, int>(int __args0, int __args1, int
    // __args2, int __args3, int __args4, int __args5, int __args6, int __args7, int __args8, int
    // __args9)
    // {
    //   return __args0 + (__args1 + (__args2 + (__args3 + (__args4 + (__args5 + (__args6 + (__args7
    //   + (__args8 + __args9))))))));
    // }
    std::cout << "constexpr fold expression sum = " << const_sum << "\n";

    // Sum v6.1 non constexpr fold expression
    // Since sum is not constexpr only the expansion is done at compile time. The evaluation is done
    // at runtime
    sum = 0;
    sum = add_fold_expresion(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    std::cout << "fold expression sum = " << sum << "\n";

    return 0;
}
