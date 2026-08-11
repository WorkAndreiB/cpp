#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "thread_safe_queue.hpp"

void producer(ThreadSafeQueue& buffer)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(10);
    while (std::chrono::steady_clock::now() < end_time)
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

void consumer(ThreadSafeQueue& buffer)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(10);  // Run the consumer for 10 seconds

    while (std::chrono::steady_clock::now() < end_time)
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
    ThreadSafeQueue buffer;

    std::vector<std::thread> workers;

    constexpr int num_producers = 2;
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