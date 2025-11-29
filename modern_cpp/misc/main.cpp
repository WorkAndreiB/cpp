#include <iostream>
#include <vector>
#include <string>

void print(const std::vector<int>& vec)
{
    for(const auto& el : vec)
    {
        std::cout << el <<" ";
    }
    std::cout <<"\n";
}

int* f()
{
    int * p = new int{20};
    return p;
}

void print(char* str)
{
	std::cout<<str<<"\n";
}

auto greeter(const std::string& salutation)
{
    return [salutation](const std::string& name){
        return salutation + " " + name;
    };
}

int main()
{
    std::cout << "Salut modern cpp\n";


    // std::vector<int> vec{1,2,3,4,5,6};

    // print(vec);

    // const char* msg="Hello World";
    // print(const_cast<char*>(msg));

    // int* p = f();
    // std::cout << "*p= " << *p <<"\n";

    // if(p)
    // {
    //     std::cout << "delete p... \n";
    //     delete p;
    // }

    // std::cout << "*p= " << *p <<"\n";

    // std::string str{"this is my string example"};

    // for(auto it = str.crbegin(); it!=str.crend(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout<<"\n";
    
    // auto it = str.begin();
    // std::advance(it,2);
    // if( it!=std::end(str))
    // {
    //     std::cout<<*it<<"\n";
    // }

    auto greet = greeter("Hello");

    std::cout << greet("Gigi") <<"\n";

    std::cout << greeter("Hello")("Mada")<<"\n";

    return 0;
}