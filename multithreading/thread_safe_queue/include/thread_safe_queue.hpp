#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <list>
#include <mutex>
#include <optional>
#include <utility>

/**
 * @brief A thread-safe FIFO queue
 *
 * All public methods are safe to call concurrently from multiple threads.
 *
 * @tparam T The type of elements stored in the queue.
 * @tparam MaxSize The maximum number of elements the queue can hold.
 *
 * @note This queue blocks on push when full and on pop when empty. Calling close()
 *       wakes blocked operations; pop() drains queued values before returning empty.
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
    /// @return False if trying to push to a closed queue.
    bool push(T value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        full_queue_cond_var.wait(lock, [this] { return list_.size() < max_size_ || closed_; });
        if (closed_)
        {
            return false;
        }

        list_.push_back(std::move(value));
        empty_queue_cond_var.notify_one();
        return true;
    }

    /**
     * @brief Blocks until an element is available or the queue is closed.
     * @return The next value, or an empty optional when closed and drained.
     */
    std::optional<T> pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        empty_queue_cond_var.wait(lock, [this] { return !list_.empty() || closed_; });
        if (list_.empty())
        {
            return std::nullopt;
        }

        T value = std::move(list_.front());
        list_.pop_front();
        full_queue_cond_var.notify_one();
        return value;
    }

    /**
     * @brief Closes the queue and wakes all blocked push() and pop() calls.
     *
     * Values already in the queue remain available to pop(). Further pushes fail.
     */
    void close()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
        }
        empty_queue_cond_var.notify_all();
        full_queue_cond_var.notify_all();
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
    bool closed_ = false;
};

#endif  // THREAD_SAFE_QUEUE_HPP
