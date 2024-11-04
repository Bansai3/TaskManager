cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(TaskManager VERSION 0.1.0 LANGUAGES CXX)

add_executable(TaskManager Task.cpp TaskManager.cpp main.cpp)

