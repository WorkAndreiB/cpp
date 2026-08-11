#include "thread_safe_queue.hpp"

#include <iostream>
#include <stdexcept>

ThreadSafeQueue::ThreadSafeQueue() : mutex_{} {}

void ThreadSafeQueue::push(int value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    list_.push_back(value);
}

int ThreadSafeQueue::pop()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (list_.empty())
    {
        throw std::runtime_error("Queue is empty");
    }
    int value = list_.front();
    list_.pop_front();
    return value;
}

void ThreadSafeQueue::print()
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto it = list_.begin(); it != list_.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

std::size_t ThreadSafeQueue::size()
{
    std::lock_guard<std::mutex> lock(mutex_);
    return list_.size();
}