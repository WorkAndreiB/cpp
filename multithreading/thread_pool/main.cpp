#include "ThreadPool.hpp"

int main()
{
    auto task = []()
    {
        std::cout << "Starting task: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Finished task: " << std::this_thread::get_id() << std::endl;
    };

    auto other_task = []()
    {
        std::cout << "Starting other task: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Finished other task: " << std::this_thread::get_id() << std::endl;
    };

    auto pool = ThreadPool(6);

    // TODO: Find a fix for this.
    // If there are more threads than tasks, some threads will block waiting for tasks.
    pool.AddTask(task);
    pool.AddTask(other_task);
    pool.AddTask(other_task);
    pool.AddTask(task);
    pool.AddTask(other_task);
    pool.AddTask(task);

    pool.Shutdown();

    return 0;
}