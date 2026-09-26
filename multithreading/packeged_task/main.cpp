#include <future>
#include <iostream>
#include <thread>

int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    // create a packaged task for adding two numbers
    std::packaged_task<int(int, int)> task(
        [](int a, int b)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return a + b;
        });

    // get the future associated with the packaged task
    std::future<int> result = task.get_future();

    // create a packaged task for waiting on the fibonacci result
    std::packaged_task<int(std::future<int>)> fib_task(
        [](std::future<int> f)
        {
            std::cout << "Waiting for fibonacci result on thread..." << std::this_thread::get_id()
                      << std::endl;
            return f.get();
        });

    // get the future associated with the fibonacci packaged task
    auto fib_thread_result = fib_task.get_future();

    std::cout << "Task started..." << std::endl;
    // start a thread with the packaged task for adding two numbers
    std::thread t(std::move(task), 2, 3);
    std::cout << "Task is running in a separate thread..." << std::endl;

    std::cout << "Calculating fibonacci(45)..." << std::endl;
    // calculate the fibonacci result asynchronously
    auto fib_result = std::async(fibonacci, 45);
    std::cout << "Waiting for fibonacci result..." << std::endl;

    // start a thread with the packaged task for waiting on the fibonacci result
    std::thread fib_thread(std::move(fib_task), std::move(fib_result));

    std::cout << "Result: " << result.get() << std::endl;

    std::cout << "Fibonacci result: " << fib_thread_result.get() << std::endl;

    // wait for the threads to finish
    t.join();
    fib_thread.join();

    return 0;
}