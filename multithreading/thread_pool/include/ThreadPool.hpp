#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <functional>
#include <thread>
#include <thread_safe_queue.hpp>
#include <vector>

using Task = std::function<void()>;

class ThreadPool
{
   private:
    ThreadSafeQueue<Task, 5> task_queue;
    std::vector<std::thread> threads;
    int thread_count;

    void DoWork();

   public:
    ThreadPool(int thread_count);
    ~ThreadPool();
    void AddTask(Task task);
    void Shutdown();
};

#endif  // THREADPOOL_HPP
