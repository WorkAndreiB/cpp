#include<iostream>
#include"print.hpp"

#include"config.hpp"

void print_hello()
{
    std::cout << "Hello world\n";

    std::cout << project_name <<"\n";

    std::cout << project_version <<"\n";
}