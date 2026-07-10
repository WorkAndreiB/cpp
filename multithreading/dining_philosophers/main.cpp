#include <array>
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Philosopher
{
   public:
    Philosopher(std::string name, int left_fork, int right_fork) :
        name_(std::move(name)), left_fork_(left_fork), right_fork_(right_fork)
    {
    }

    std::string get_name() const
    {
        return name_;
    }

    int get_left_fork() const
    {
        return left_fork_;
    }

    int get_right_fork() const
    {
        return right_fork_;
    }

    void increment_eat_count()
    {
        ++eat_count_;
    }

    int get_eat_count() const
    {
        return eat_count_;
    }

   private:
    std::string name_;
    int left_fork_;
    int right_fork_;

    std::atomic<int> eat_count_{0};
};

constexpr int philosophers_number = 5;
constexpr auto thinking_time = std::chrono::seconds(3);
constexpr auto eating_time = std::chrono::seconds(1);

std::array<Philosopher, philosophers_number> philosophers = {
    Philosopher{"Aristotle", 0, 1}, Philosopher{"Kant", 1, 2},    Philosopher{"Spinoza", 2, 3},
    Philosopher{"Marx", 3, 4},      Philosopher{"Russell", 4, 0},
};

std::array<std::mutex, philosophers_number> forks = {
    std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(),
};

void print(std::mutex& print_mutex, int philosopher_index, const std::string& message)
{
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << "Philosopher " << philosophers[philosopher_index].get_name() << " " << message
              << std::endl;
}

void dine_and_think(std::mutex& print_mutex, int philosopher_index)
{
    while (true)
    {
        print(print_mutex, philosopher_index, "is_thinking");
        std::this_thread::sleep_for(thinking_time);

        print(print_mutex, philosopher_index, "is_hungry");
        auto& philosopher = philosophers.at(philosopher_index);

        print(print_mutex, philosopher_index,
              "is_trying_to_pick_up_forks (" + std::to_string(philosopher.get_left_fork()) + ", " +
                  std::to_string(philosopher.get_right_fork()) + ")");

        {
            // Use std::scoped_lock to lock both forks at once, preventing deadlock
            std::scoped_lock lock(forks.at(philosopher.get_left_fork()),
                                  forks.at(philosopher.get_right_fork()));

            print(print_mutex, philosopher_index,
                  "has_picked_up_forks (" + std::to_string(philosopher.get_left_fork()) + ", " +
                      std::to_string(philosopher.get_right_fork()) + ")");

            print(print_mutex, philosopher_index, "is_eating");
            philosopher.increment_eat_count();
            std::this_thread::sleep_for(eating_time);

            print(print_mutex, philosopher_index,
                  "is_putting_down_forks (" + std::to_string(philosopher.get_left_fork()) + ", " +
                      std::to_string(philosopher.get_right_fork()) + ")");
        }

        print(print_mutex, philosopher_index,
              "has_finished_eating and has eaten " + std::to_string(philosopher.get_eat_count()) +
                  " times");
    }
}

int main()
{
    std::mutex print_mutex;

    std::vector<std::thread> threads;
    for (int i = 0; i < philosophers_number; ++i)
    {
        threads.push_back(std::thread(dine_and_think, std::ref(print_mutex), i));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
