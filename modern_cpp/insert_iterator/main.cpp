#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

/*
 * Call to print_vector can be done without specifying template parameter in some cases
 * When possible, the compiler will deduce the missing template arguments from the function
 * arguments.
 */
template <typename T>
void print_vector(std::vector<T> vec)
{
    for (const auto& el : vec)
    {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

void read_data_from_cin_and_push_to_vector()
{
    std::cout << "Enter some words:\n";

    std::istream_iterator<std::string> str_iterator_istream(std::cin);
    std::istream_iterator<std::string> eof;

    std::vector<std::string> words;
    auto it = std::back_inserter(words);

    while (str_iterator_istream != eof)
    {
        it = *str_iterator_istream;
        ++str_iterator_istream;
    }

    std::cout << "Words:\n";
    print_vector(words);
}

void init_vector_with_n_values()
{
    std::vector<int> vec;
    std::fill_n(std::back_inserter(vec), 5, 100);

    print_vector(vec);
}

void fill_vector_with_generated_values()
{
    std::vector<int> vec(10);
    std::generate(vec.begin(), vec.end(),
                  [n = 0]() mutable
                  {
                      ++n;
                      return n * n;
                  });

    print_vector(vec);
}

// copy element from one vector to another
void copy_element_to_vector()
{
    std::vector<int> v_source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v_destination(v_source.size());

    std::copy(v_source.cbegin(), v_source.cend(), v_destination.begin());

    print_vector(v_source);
    print_vector(v_destination);
}

// copy element from one vector to another using back_inserter
void copy_element_to_vector2()
{
    std::vector<int> v_source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v_destination;

    std::copy(v_source.cbegin(), v_source.cend(), std::back_inserter(v_destination));

    print_vector(v_source);
    print_vector(v_destination);
}

// copy first n element from one vector to another
void copy_first_n_element_to_vector()
{
    std::vector<int> v_source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v_destination;
    int num_of_element_to_copy{5};

    std::copy_n(v_source.cbegin(), num_of_element_to_copy, std::back_inserter(v_destination));

    print_vector(v_source);
    print_vector(v_destination);
}

// copy elements from one vector to another if they comply to condition
void copy_element_if()
{
    std::vector<int> v_source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v_destination;

    std::copy_if(v_source.cbegin(), v_source.cend(), std::back_inserter(v_destination),
                 [](int el) { return el % 2 == 0; });

    print_vector(v_source);
    print_vector(v_destination);
}

std::array<int, 5> get_array()
{
    std::array<int, 5> arr{1, 2, 3, 4, 5};

    return arr;
}

std::vector<int> get_vector()
{
    std::vector<int> vec{1, 2, 3, 4, 5};

    return vec;
}

int main()
{
    // read_data_from_cin_and_push_to_vector();
    // init_vector_with_n_values();
    // fill_vector_with_generated_values();
    // copy_element_to_vector();
    // copy_element_to_vector2();
    // copy_first_n_element_to_vector();
    // copy_element_if();

    auto arr = get_array();

    for (const auto& el : arr)
    {
        std::cout << el << " ";
    }
    std::cout << "\n";

    auto vec = get_vector();
    print_vector(vec);

    std::cout << "\n";
    return 0;
}