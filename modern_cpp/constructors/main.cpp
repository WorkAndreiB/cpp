#include <cstring>
#include <iostream>

class MyString
{
   private:
    int size;
    char* data;

   public:
    MyString() = default;

    MyString(int size, char* str) : size(size), data(new char[size])
    {
        std::cout << "parameter constructor\n";

        std::memcpy(data, str, std::min(size - 1, static_cast<int>(strlen(str))));
        data[size - 1] = '\0';
    }

    // copy constructor
    MyString(const MyString& other) : size(other.size), data(nullptr)
    {
        std::cout << "copy constructor\n";
        if (other.data)
        {
            data = new char[size];
            std::memcpy(data, other.data, size);
        }
    }
    // copy operator
    MyString& operator=(const MyString& other)
    {
        std::cout << "operator =\n";
        size = other.size;

        if (data)
        {
            std::cout << "assigning to an already initialized objects. delete old data to prevent "
                         "memory leak\n";
            delete[] data;
        }

        data = new char[size];
        std::memcpy(data, other.data, size);

        return *this;
    }

    // move constructor
    MyString(MyString&& other) : size(other.size), data(other.data)
    {
        std::cout << "Move constructor\n";
        other.data = nullptr;
        other.size = 0;
    }

    // move assignment operator
    MyString& operator=(MyString&& other)
    {
        std::cout << "move operator =\n";
        if (this != &other)
        {
            if (data)
            {
                delete[] data;
            }
            else
            {
                std::cout << "data is not initialized\n";
            }

            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~MyString()
    {
        if (data != nullptr)
        {
            std::cout << "destructor: " << static_cast<void*>(data) << "\n";
            delete[] data;
            data = nullptr;
        }
        else
        {
            std::cout << "already deleted\n";
        }
    }

    void print()
    {
        if (data)
        {
            std::cout << "data: " << data << ": addr: " << static_cast<void*>(data) << "\n";
        }
        else
        {
            std::cout << "invalid data\n";
        }
    }
};

void print(MyString str)
{
    str.print();
}

MyString createString()
{
    return MyString(10, "Hello");
}

int main()
{
    // copy constructor not called because of optimizations (copy elision)
    MyString other_str = createString();
    other_str.print();

    {
        MyString str(10, "Salut!");
        MyString str2(str);
        MyString str3 = str2;

        std::cout << "Send argument to function by value\n";
        print(str);

        str.print();
        str2.print();
        str3.print();

        str3 = str;
        str3.print();

        MyString str4(std::move(str3));
        str3.print();
        str4.print();

        MyString str5{};
        str5 = std::move(str);
        str.print();
        str5.print();
    }

    std::cout << "The end\n";
}