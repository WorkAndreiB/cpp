#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "thread_safe_queue.hpp"

using Buffer = ThreadSafeQueue<int, 5>;

void producer(Buffer& buffer)
{
    for (int i = 0; i < 20; ++i)
    {
        // simulate time taken to produce an item
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        static thread_local std::mt19937 rng{std::random_device{}()};
        static thread_local std::uniform_int_distribution<int> dist(0, 99);
        int item = dist(rng);  // produce a random item
        buffer.push(item);
        buffer.print();
    }
}

void consumer(Buffer& buffer)
{
    for (int i = 0; i < 20; ++i)
    {
        try
        {
            buffer.pop();
            buffer.print();
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(210));
    }
}

int main()
{
    Buffer buffer;

    std::vector<std::thread> workers;

    constexpr int num_producers = 4;
    constexpr int num_consumers = 4;

    for (int i = 0; i < num_producers; ++i)
    {
        workers.emplace_back(producer, std::ref(buffer));
    }

    for (int i = 0; i < num_consumers; ++i)
    {
        workers.emplace_back(consumer, std::ref(buffer));
    }

    for (auto& worker : workers)
    {
        worker.join();
    }

    return 0;
}