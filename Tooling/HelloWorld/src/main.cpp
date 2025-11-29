#include "print.hpp"
#include <iostream>

#include <nlohmann/json.hpp>

int main()
{
    print_hello();

    std::cout << "Json lib version: " 
    << NLOHMANN_JSON_VERSION_MAJOR<<"."
    << NLOHMANN_JSON_VERSION_MINOR<<"\n";

    return 0;
}