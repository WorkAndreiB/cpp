#include "ThreadPool.hpp"

#include <stdexcept>
#include <utility>

ThreadPool::ThreadPool(int thread_count) : thread_count(thread_count)
{
    if (thread_count <= 0)
    {
        throw std::invalid_argument("thread_count must be greater than zero");
    }
    for (int i = 0; i < thread_count; ++i)
    {
        threads.emplace_back(&ThreadPool::DoWork, this);
    }
}

ThreadPool::~ThreadPool()
{
    std::cout << "Destroying ThreadPool" << std::endl;
    Shutdown();
    for (auto &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    std::cout << "ThreadPool destroyed" << std::endl;
}

void ThreadPool::DoWork()
{
    while (true)
    {
        auto task = task_queue.pop();
        if (!task.has_value())
        {
            return;
        }
        task.value()();
    }
}

void ThreadPool::AddTask(std::function<void()> task)
{
    if (!task_queue.push(std::move(task)))
    {
        throw std::logic_error("Cannot add a task to a shut down ThreadPool");
    }
}

void ThreadPool::Shutdown()
{
    task_queue.close();
}