#include <iostream>
#include <cstring>

class MyString{
private:
    int size;
    char* data;
public:
    MyString() = default;

    MyString(int size, char* str): size(size), data(new char[size]){
        std::cout << "parameter constructor\n";

        for(size_t i=0; i<strlen(str); ++i)
        {
            data[i] = str[i];
        }
    } 

    // copy constructor
    MyString(const MyString& other): size(other.size)
    {
        std::cout << "copy constructor\n";
        data = new char[size];
        for(int i=0; i<size; ++i)
        {
            data[i] = other.data[i];
        }
    }
    // copy operator
    MyString& operator=(const MyString& other)
    {
        std::cout <<"operator =\n";
        size = other.size;
        data = new char[size];
        
        for(int i = 0; i<size; ++i)
        {
            data[i]=other.data[i];
        }
        return *this;
    }

    // move constructor
    MyString(MyString&& other)
    {
        std::cout << "Move constructor\n";
        size = other.size;
        data = other.data;
        other.data = nullptr;
    }

    // move assignment operator
    MyString& operator=(MyString&& other)
    {
        std::cout << "move operator =\n";
        if(this != &other)
        {
            if(data)
            {
                delete [] data;
            }
            else{
                std::cout << "data is not initialized\n";
            }
            
            data = other.data;
            size = other.size;

            other.data = nullptr;
        }
        return *this;
    }

    ~MyString()
    {
        if(data != nullptr)
        {
            std::cout <<"destructor: "<< static_cast<void*>(data) << "\n";
            delete [] data;
        }
        else
        {
            std::cout <<"already deleted\n";
        }
      
    }

    void print()
    {
        std::cout<<"data: " << data << ": addr: " << static_cast<void*>(data) <<"\n";
    }
};

int main()
{
    MyString str(10, "Salut!");

    MyString str2(str);

    MyString str3;
    str3 = str2;

    str.print();

    str2.print();
    str3.print();

    MyString str4(std::move(str3));

    MyString str5{};
    str5 = std::move(str);
}