#include <algorithm>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

long long accumulate(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end)
{
    return std::accumulate(begin, end, 0);
}

long long add_parallel(const std::vector<int> &data)
{
    auto size = data.size();
    auto step = size / 10;
    auto result1 = std::async(accumulate, data.begin(), data.begin() + step);
    auto result2 = std::async(accumulate, data.begin() + step, data.begin() + 2 * step);
    auto result3 = std::async(accumulate, data.begin() + 2 * step, data.begin() + 3 * step);
    auto result4 = std::async(accumulate, data.begin() + 3 * step, data.begin() + 4 * step);
    auto result5 = std::async(accumulate, data.begin() + 4 * step, data.begin() + 5 * step);
    auto result6 = std::async(accumulate, data.begin() + 5 * step, data.begin() + 6 * step);
    auto result7 = std::async(accumulate, data.begin() + 6 * step, data.begin() + 7 * step);
    auto result8 = std::async(accumulate, data.begin() + 7 * step, data.begin() + 8 * step);
    auto result9 = std::async(accumulate, data.begin() + 8 * step, data.begin() + 9 * step);
    auto result10 = std::async(accumulate, data.begin() + 9 * step, data.end());

    return result1.get() + result2.get() + result3.get() + result4.get() + result5.get() +
           result6.get() + result7.get() + result8.get() + result9.get() + result10.get();
}

int main()
{
    int num_elements = 10000000;
    std::vector<int> data(num_elements);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (auto &d : data)
        d = dis(gen);

    // std::cout << "Generated data: ";
    // for (const auto &d : data)
    //     std::cout << d << " ";
    // std::cout << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "Sum: " << add_parallel(data) << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    auto sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    end_time = std::chrono::high_resolution_clock::now();
    elapsed = end_time - start_time;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}