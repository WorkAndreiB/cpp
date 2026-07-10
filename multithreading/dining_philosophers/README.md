# Dining Philosophers

A classic concurrency problem originally formulated by Edsger Dijkstra, used to illustrate the challenges of deadlock, livelock, and starvation in multithreaded programs.

## The problem

Five philosophers sit around a circular table. Between each pair of neighbours is one fork, giving five forks in total. Each philosopher alternates between two states:

- **Thinking** — the philosopher does not need any forks.
- **Eating** — the philosopher must hold *both* the left and right fork simultaneously.

Because each fork is shared between two philosophers, a naive approach of "pick up the left fork, then the right fork" can deadlock: every philosopher picks up their left fork at the same time and waits forever for the right fork.

## Deadlock prevention

This implementation uses `std::scoped_lock` to acquire both forks in a single atomic operation:

```cpp
std::scoped_lock lock(forks.at(philosopher.get_left_fork()),
                      forks.at(philosopher.get_right_fork()));
```

`std::scoped_lock` (C++17) accepts multiple mutexes and locks them together using a deadlock-avoidance algorithm. No philosopher can hold one fork while blocked on the other, eliminating the circular-wait condition that causes deadlock.


## Key concurrency primitives used

- `std::scoped_lock` — simultaneous deadlock-safe acquisition of multiple mutexes.
- `std::lock_guard` — RAII guard for the print mutex.
- `std::atomic<int>` — atomic eat counter per philosopher.
- `std::thread` / `std::this_thread::sleep_for` — thread creation and sleeping.

## Build and run

From `multithreading/dining_philosophers`:

```bash
cmake -S . -B build
cmake --build build
./build/DiningPhilosophers
```

