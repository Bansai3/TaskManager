#include<mutex>
#include<queue>
#include<thread>
#include <ctime>
#include <chrono>
#include <functional>
#include <iostream>
#include "Task.h"


class TaskManager {
private:
    std::mutex mtx;
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> tasks;
    std::vector<std::thread> threads;
    int threads_count;
    std::atomic<bool> stop_flag;
    std::condition_variable cv;

    bool check_threads(int threads_count);
public:
    TaskManager(int threads_count);

    void Add(std::function<void()> task, std::time_t timestamp);
    void run();

    ~TaskManager();
};