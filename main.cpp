#include <iostream>
#include "TaskManager.h"

int main(int, char**){
    TaskManager tm(10);

    std::vector<std::pair<std::function<void()>, std::time_t>> vec;
    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            vec.push_back({[i, j]() { std::cout << "Task " << i << "_" << j << std::endl; }, std::time(0) + i});
        }
    }

    for (auto& el : vec) {
        tm.Add(el.first, el.second);
    }

    return 0;
}
