#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::string data;

std::mutex data_mtx;

std::condition_variable data_cv;

bool update_progress = false;
bool download_completed = false;

void download_data()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Fetcher thread is downloading data..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));  // Simulate downloading data

        std::unique_lock<std::mutex> lock(data_mtx);
        data += "Data block " + std::to_string(i) + "\n";  // Append downloaded data
        std::cout << "Downloaded data :\n" << data << std::endl;

        update_progress = true;  // Set the update progress flag to true
        lock.unlock();

        data_cv.notify_all();  // Notify all waiting threads that data has been updated
    }

    std::cout << "Data download completed." << std::endl;

    {
        std::lock_guard<std::mutex> lock(data_mtx);
        download_completed = true;  // Set the download completed flag to true
    }
    data_cv.notify_all();  // Notify all waiting threads that download is completed
}

void progress_bar()
{
    while (true)
    {
        std::cout << "Progress bar thread is waiting for data update..." << std::endl;

        std::unique_lock<std::mutex> lock(data_mtx);
        data_cv.wait(lock, []() { return update_progress || download_completed; });

        if (update_progress)
        {
            std::size_t data_size = data.size();
            std::cout << "Progress bar thread received data update. Current data size: "
                      << data_size << std::endl;
            update_progress = false;  // Reset the update progress flag
        }

        if (download_completed)
        {
            std::cout << "Progress bar thread detected download completion. Exiting..."
                      << std::endl;
            break;  // Exit the loop if download is completed
        }
    }
}

void process_data()
{
    std::cout << "Processor thread is waiting for download completion..." << std::endl;
    std::string copy_data;

    // Wait for download completion
    {
        std::unique_lock<std::mutex> lock(data_mtx);
        data_cv.wait(
            lock, []()
            { return download_completed; });  // Wait for the download completed flag to be true

        std::cout << "Copying downloaded data for processing..." << std::endl;
        copy_data = data;  // Copy the downloaded data for processing
    }

    std::cout << "Processor thread detected download completion. Processing data..." << std::endl;
    std::cout << "Final downloaded data:\n" << copy_data << std::endl;
}

int main()
{
    std::thread fetcher_thread(download_data);
    std::thread progress_thread(progress_bar);
    std::thread processor_thread(process_data);

    fetcher_thread.join();
    progress_thread.join();
    processor_thread.join();

    return 0;
}