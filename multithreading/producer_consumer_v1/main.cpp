#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

void producer(std::queue<int>& buffer, std::timed_mutex& mtx, const std::size_t max_buffer_size)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(10);
    while (std::chrono::steady_clock::now() < end_time)
    {
        // simulate time taken to produce an item
        // because unique_lock is used, the time taken to produce an item is not included in the
        // critical section, so other thread can access the buffer while the producer is
        // producing an item
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::timed_mutex> lock(mtx);
        if (buffer.size() < max_buffer_size)
        {
            int item = rand() % 100;  // Produce a random item
            buffer.push(item);
            lock.unlock();
            std::cout << "Produced: " << item << "\n";
        }
        else
        {
            std::cout << "Buffer is full, producer is waiting...\n";
        }
    }
}

void consumer(std::queue<int>& buffer, std::timed_mutex& mtx)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(10);  // Run the consumer for 10 seconds

    // use defer_lock to create the unique_lock without locking the mutex
    std::unique_lock<std::timed_mutex> lock(mtx, std::defer_lock);

    while (std::chrono::steady_clock::now() < end_time)
    {
        // because unique_lock is used, unlock is called to end the critical section before the
        // time taken to consume an item, so other thread can access the buffer while the
        // consumer is consuming an item
        if (lock.try_lock_for(std::chrono::seconds(1)))
        {
            if (buffer.size() > 0)
            {
                int item = buffer.front();
                buffer.pop();
                std::cout << "Consumed: " << item << "\n";
            }
            else
            {
                std::cout << "Buffer is empty, consumer is waiting...\n";
            }
            lock.unlock();
            // simulate time taken to consume an item
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        else
        {
            std::cout << "Consumer waited 1 second to acquire the mutex...\n";
        }
    }
}

int main()
{
    std::queue<int> buffer;
    std::timed_mutex mtx;
    const std::size_t max_buffer_size = 5;

    // This thread will lock the mutex for 5 seconds to demonstrate that the producer and consumer
    // threads will be blocked until the mutex is unlocked
    std::thread blocking_thread(
        [&mtx]()
        {
            std::lock_guard<std::timed_mutex> lock(mtx);
            std::cout << "Blocking thread has locked the mutex for 5 seconds...\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        });

    std::thread th_producer(producer, std::ref(buffer), std::ref(mtx), max_buffer_size);
    std::thread th_consumer(consumer, std::ref(buffer), std::ref(mtx));

    blocking_thread.join();
    th_producer.join();
    th_consumer.join();

    return 0;
}