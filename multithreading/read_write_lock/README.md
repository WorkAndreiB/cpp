# Read-Write Lock Demo

This example shows how to use `std::shared_mutex` to let multiple reader threads access a shared value at the same time while still giving writer threads exclusive access.

## What the program does

The program creates a shared integer `x` and a `std::shared_mutex` that protects it.

It then starts three groups of threads:

1. One writer increments `x`.
2. Twenty readers print the current value of `x`.
3. A second writer increments `x` again.
4. Twenty more readers print the updated value.

The output is intentionally nondeterministic because thread scheduling is handled by the operating system.

## Locking model

The example uses two different lock types:

- `std::unique_lock<std::shared_mutex>` in `write()` for exclusive access.
- `std::shared_lock<std::shared_mutex>` in `read()` for concurrent read access.

That means:

- Any number of reader threads can hold the lock together.
- Only one writer can hold the lock at a time.
- Writers block readers, and readers block writers, while the lock is held.

## Why this matters

This pattern is useful when reads are frequent and writes are rare. Compared with a plain `std::mutex`, `std::shared_mutex` can improve throughput because readers do not need to serialize with each other.

## Build and run

From `multithreading/read_write_lock`:

```bash
cmake -S . -B build
cmake --build build
./build/ReadWrite
```

## Notes

- The reader function sleeps for 100 ms while holding the shared lock so the overlap between readers is easier to observe.
- The commented-out lock lines in the source show the alternative exclusive-lock approach, but the example intentionally uses shared and unique locks to demonstrate the read-write behavior.
