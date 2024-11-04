#include "TaskManager.h"

TaskManager::TaskManager(int threads_count) {
    if (check_threads(threads_count) == false) {
        throw "Invalid threads count! Threads count must be > 0!";
    }
    stop_flag = false;
    for (int i = 0; i < threads_count; ++i) {
        threads.emplace_back(&TaskManager::run, this);
    }
}

void TaskManager::Add(std::function<void()> task, std::time_t timestamp) {
    {
        std::lock_guard lk(mtx);
        tasks.push(Task(task, timestamp));
    }
    cv.notify_one();
}

void TaskManager::run() {
    while(true) {
        std::unique_lock<std::mutex> lock(mtx);
        if (stop_flag && tasks.empty()) break;

        if (!tasks.empty()) {
            auto now = std::time(0);
            auto top_task = tasks.top();

            if (top_task.get_time() <= now) {
                tasks.pop();
                lock.unlock();
                top_task.get_function()();
            } else {
                cv.wait_until(lock, std::chrono::system_clock::from_time_t(top_task.get_time()));
            }
        } else {
            cv.wait(lock);
        }
    }
}

TaskManager::~TaskManager() {
    stop_flag = true;
    cv.notify_all();
    for (std::thread& thread : threads) {
        thread.join();
    }
}

bool TaskManager::check_threads(int threads_count) {
    return threads_count > 0;
}