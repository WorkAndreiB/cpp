#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

bool condition = false;

void reader(std::string& data, std::mutex& mtx, std::condition_variable& cv)
{
    std::unique_lock<std::mutex> u_lock(mtx);
    std::cout << "Reader thread is waiting for data..." << std::endl;
    cv.wait(u_lock, []() { return condition; });  // Wait for the condition variable to be notified
    std::cout << "Reader thread has been notified. Processing data..." << std::endl;
    std::cout << "Reader thread received data: " << data << std::endl;
}

void writer(std::string& data, std::mutex& mtx, std::condition_variable& cv)
{
    std::cout << "Writer thread is preparing to lock mutex" << std::endl;
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate some work
        data = "Hello from writer thread!" +
               std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));
        std::cout << "Writer thread has written data: " << data << std::endl;
        condition = true;  // Set the condition to true
    }
    cv.notify_one();  // Notify the waiting reader thread
}

int main()
{
    std::string data;
    std::mutex mtx;
    std::condition_variable cv;

    // std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Ensure writer starts first

    std::thread writer_th(writer, std::ref(data), std::ref(mtx), std::ref(cv));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::thread reader_th(reader, std::ref(data), std::ref(mtx), std::ref(cv));

    writer_th.join();
    reader_th.join();

    return 0;
}
