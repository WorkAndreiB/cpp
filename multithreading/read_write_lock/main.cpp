#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

void write(std::shared_mutex& mtx, int& x)
{
    // std::lock_guard<std::shared_mutex> lock(mtx);
    // use unique_lock to acquire the exclusive lock for writing
    std::unique_lock<std::shared_mutex> lock(mtx);
    ++x;
}

void read(std::shared_mutex& mtx, int& x)
{
    // std::unique_lock<std::shared_mutex> lock(mtx);
    // use shared_lock to acquire the shared lock for reading
    std::shared_lock<std::shared_mutex> lock(mtx);
    std::cout << "x: " << x << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main()
{
    std::shared_mutex mtx;
    int x = 0;

    std::vector<std::thread> threads;

    threads.push_back(std::thread(write, std::ref(mtx), std::ref(x)));

    for (int i = 0; i < 20; ++i)
    {
        threads.push_back(std::thread(read, std::ref(mtx), std::ref(x)));
    }

    threads.push_back(std::thread(write, std::ref(mtx), std::ref(x)));

    for (int i = 0; i < 20; ++i)
    {
        threads.push_back(std::thread(read, std::ref(mtx), std::ref(x)));
    }

    for (auto& t : threads)
    {
        t.join();
    }
}