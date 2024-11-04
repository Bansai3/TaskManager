#include <functional>

class Task {
private:
    std::function<void()> f;
    std::time_t time;
public:
    Task(std::function<void()> f, std::time_t time);

    std::function<void()> get_function() const;

    std::time_t get_time() const;

    bool operator>(const Task &other) const;
};