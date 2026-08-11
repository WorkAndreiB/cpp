#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <cstddef>
#include <list>
#include <mutex>

/**
 * @brief A thread-safe FIFO queue backed by a mutex.
 *
 * All public methods are safe to call concurrently from multiple threads.
 */
class ThreadSafeQueue
{
   public:
    ThreadSafeQueue();

    /// @brief Pushes a value onto the back of the queue.
    /// @param value The integer to enqueue.
    void push(int value);

    /**
     * @brief Removes and returns the front element.
     * @return The integer at the front of the queue.
     * @throws std::runtime_error if the queue is empty.
     */
    int pop();

    /// @brief Prints all elements in the queue to stdout.
    void print();

    /// @brief Returns the number of elements currently in the queue.
    std::size_t size();

   private:
    std::list<int> list_;
    std::mutex mutex_;
};

#endif  // THREAD_SAFE_QUEUE_HPP
