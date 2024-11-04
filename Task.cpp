#include "Task.h"

Task::Task(std::function<void()> f, std::time_t time) {
    this->f = f;
    this->time = time;
}

std::function<void()> Task::get_function() const {
    return f;
}

std::time_t Task::get_time() const {
    return time;
}

bool Task::operator>(const Task &other) const {
    return time > other.time;
}