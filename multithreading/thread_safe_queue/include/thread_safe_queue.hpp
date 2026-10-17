#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <list>
#include <mutex>

/**
 * @brief A thread-safe FIFO queue
 *
 * All public methods are safe to call concurrently from multiple threads.
 *
 * @tparam T The type of elements stored in the queue.
 * @tparam MaxSize The maximum number of elements the queue can hold.
 *
 * @note This queue blocks on push when full and on pop when empty.
 *
 */
template <typename T, size_t MaxSize>
class ThreadSafeQueue
{
   public:
    ThreadSafeQueue() = default;

    /**
     * @brief Deleted copy and move constructors and assignment operators to prevent copying and
     * moving.
     */
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

    /// @brief Pushes a value onto the back of the queue.
    /// @param value The value to enqueue.
    void push(T value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        full_queue_cond_var.wait(lock, [this] { return list_.size() < max_size_; });
        list_.push_back(value);
        empty_queue_cond_var.notify_one();
    }

    /**
     * @brief Blocks until an element is available, then removes and returns it.
     * @return The value at the front of the queue.
     */
    T pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        empty_queue_cond_var.wait(lock, [this] { return !list_.empty(); });
        T value = list_.front();
        list_.pop_front();
        full_queue_cond_var.notify_one();
        return value;
    }

    /// @brief Prints all elements in the queue to stdout.
    void print()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto it = list_.begin(); it != list_.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return list_.empty();
    }

   private:
    std::list<T> list_;
    static_assert(MaxSize > 0, "ThreadSafeQueue MaxSize must be greater than zero");
    static constexpr size_t max_size_ = MaxSize;
    std::mutex mutex_;
    std::condition_variable empty_queue_cond_var;
    std::condition_variable full_queue_cond_var;
};

#endif  // THREAD_SAFE_QUEUE_HPP
