# Condition Variables — Download Pipeline Demo

A multithreaded C++ program demonstrating `std::condition_variable` coordination between producer, monitor, and consumer threads.

---

## Overview

The program simulates a data download pipeline using three threads:

| Thread | Function | Role |
|---|---|---|
| `fetcher_thread` | `download_data()` | Downloads data in blocks (producer) |
| `progress_thread` | `progress_bar()` | Reports progress after each block (monitor) |
| `processor_thread` | `process_data()` | Processes all data after download completes (consumer) |

---

## Shared State

| Variable | Type | Protected By | Purpose |
|---|---|---|---|
| `data` | `std::string` | `data_mtx` | Accumulates downloaded data blocks |
| `update_progress` | `bool` | `data_mtx` | Signals a new data block is available |
| `download_completed` | `bool` | `completed_mtx` | Signals the entire download is done |
| `data_cv` | `std::condition_variable` | — | Wakes `progress_bar` on new block |
| `completed_cv` | `std::condition_variable` | — | Wakes `progress_bar` and `process_data` on completion |

---

## Thread Details

### `download_data()` — Fetcher

Loops 5 times, each iteration:
1. Sleeps 2 seconds (simulates network I/O)
2. Acquires `data_mtx`, appends `"Data block N\n"` to `data`
3. Sets `update_progress = true`, releases the lock
4. Calls `data_cv.notify_one()` to wake the progress bar

After the loop:
- Acquires `completed_mtx`
- Sets `download_completed = true`
- Calls `completed_cv.notify_one()` to wake the processor

---

### `progress_bar()` — Monitor

Runs in a loop until the download is complete:

**Step 1 — Wait for a data update:**
```cpp
std::unique_lock<std::mutex> lock(data_mtx);
data_cv.wait(lock, []() { return update_progress; });
```
Blocks until `update_progress` is `true`, then reads `data.size()` and resets the flag.

**Step 2 — Check for download completion:**
```cpp
completed_cv.wait_for(lock, std::chrono::milliseconds(100),
                      []() { return download_completed; });
```
Waits up to 100 ms for `download_completed`. If `true`, exits the loop.

---

### `process_data()` — Processor

1. Waits indefinitely on `completed_cv` until `download_completed` is `true`
2. Acquires `data_mtx` and copies `data` into a local string
3. Prints the full downloaded dataset

---

## Synchronization Pattern

This program uses the **predicate overload** of `wait` / `wait_for` to guard against spurious wakeups:

```cpp
// Equivalent to:
while (!predicate()) cv.wait(lock);

// Written as:
cv.wait(lock, predicate);
```

This ensures a thread re-checks the condition before proceeding even if it wakes up without a notification.

---

## Building

```bash
cmake -S . -B build
cmake --build build
./build/ConditionVariables
```
