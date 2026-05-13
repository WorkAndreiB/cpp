#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

void increment(std::atomic<int>& counter)
{
    for (auto i = 0; i < 100000; ++i)
    {
        ++counter;
    }
}

void work(const std::string& task_name, int duration)
{
    for (auto i = 0; i < 5; ++i)
    {
        std::cout << "Working on " << task_name << "... " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(duration));
    }
    std::cout << task_name << " completed." << std::endl;
}

void work_with_mutex(int& count, std::mutex& mtx)
{
    for (auto i = 0; i < 100000; ++i)
    {
        mtx.lock();
        ++count;
        mtx.unlock();
    }
}

void work_with_lock_guard(int& count, std::mutex& mtx)
{
    for (auto i = 0; i < 100000; ++i)
    {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
    }
}

class CallableObject
{
   private:
    int count{0};
    std::mutex mtx;

   public:
    void operator()()
    {
        for (auto i = 0; i < 100000; ++i)
        {
            std::lock_guard<std::mutex> lock(mtx);
            ++count;
        }
    }

    int getCount() const
    {
        return count;
    }
};

class MyClass
{
   public:
    void work()
    {
        for (auto i = 0; i < 5; ++i)
        {
            std::cout << "MyClass working... " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "MyClass work completed." << std::endl;
    }

    static void staticWork()
    {
        for (auto i = 0; i < 5; ++i)
        {
            std::cout << "MyClass static working... " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main()
{
    std::cout << "Starting work..." << std::endl;

    std::thread t1(work, "Task 1", 1);
    std::thread t2(work, "Task 2", 2);
    std::thread t3(
        []()
        {
            for (auto i = 0; i < 10; ++i)
            {
                std::cout << "Lambda task running... " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            std::cout << "Lambda task completed." << std::endl;
        });

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Work completed." << std::endl;

    /***atomic***/
    std::atomic<int> counter = 0;
    std::thread t4(increment, std::ref(counter));
    std::thread t5(increment, std::ref(counter));

    t4.join();
    t5.join();

    std::cout << "Final counter value: " << counter << std::endl;

    /***mutex***/
    int count = 0;
    std::mutex mtx;
    std::thread t6(work_with_mutex, std::ref(count), std::ref(mtx));
    std::thread t7(work_with_mutex, std::ref(count), std::ref(mtx));

    t6.join();
    t7.join();

    std::cout << "Final count value: " << count << std::endl;

    /***lock_guard***/
    int count2 = 0;
    std::mutex mtx2;
    std::thread t8(work_with_lock_guard, std::ref(count2), std::ref(mtx2));
    std::thread t9(work_with_lock_guard, std::ref(count2), std::ref(mtx2));

    t8.join();
    t9.join();

    std::cout << "Final count2 value: " << count2 << std::endl;

    /***callable object***/
    CallableObject obj;
    std::thread t10(std::ref(obj));
    std::thread t11(std::ref(obj));

    t10.join();
    t11.join();

    std::cout << "Final callable object count: " << obj.getCount() << std::endl;

    /***class member function***/
    MyClass my_class;
    std::thread t12(&MyClass::work, &my_class);

    t12.join();

    /***class static member function***/
    std::thread t13(&MyClass::staticWork);

    t13.join();

    std::cout << "All tasks completed." << std::endl;

    return 0;
}