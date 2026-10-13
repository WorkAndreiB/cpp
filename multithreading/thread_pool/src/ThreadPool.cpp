#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int thread_count) : thread_count(thread_count)
{
    for (int i = 0; i < thread_count; ++i)
    {
        threads.emplace_back(&ThreadPool::DoWork, this);
    }
}

ThreadPool::~ThreadPool()
{
    std::cout << "Destroying ThreadPool" << std::endl;
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
    while (!shutdown)
    {
        auto task = task_queue.pop();
        task();
    }
}

void ThreadPool::AddTask(std::function<void()> task)
{
    task_queue.push(task);
}

void ThreadPool::Shutdown()
{
    shutdown = true;
}