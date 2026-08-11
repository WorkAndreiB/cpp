#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "thread_safe_queue.hpp"

void producer(ThreadSafeQueue& buffer, const std::size_t max_buffer_size)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(10);
    while (std::chrono::steady_clock::now() < end_time)
    {
        // simulate time taken to produce an item
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (buffer.size() < max_buffer_size)
        {
            int item = std::rand() % 100;  // produce a random item
            buffer.push(item);
            buffer.print();
        }
        else
        {
            std::cout << "Buffer is full, producer is waiting...\n";
        }
    }
    std::cout << "Producer finished producing items.\n";
}

void consumer(ThreadSafeQueue& buffer)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(10);  // Run the consumer for 10 seconds

    while (std::chrono::steady_clock::now() < end_time)
    {
        if (buffer.size() > 0)
        {
            buffer.pop();
            buffer.print();
        }
        else
        {
            std::cout << "Buffer is empty, consumer is waiting...\n";
        }
        // simulate time taken to consume an item
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "Consumer finished consuming items.\n";
}

int main()
{
    ThreadSafeQueue buffer;
    const std::size_t max_buffer_size = 10;

    std::vector<std::thread> workers;

    constexpr int num_producers = 2;
    constexpr int num_consumers = 5;

    for (int i = 0; i < num_producers; ++i)
    {
        workers.emplace_back(producer, std::ref(buffer), max_buffer_size);
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