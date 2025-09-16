cmake_minimum_required(VERSION 3.28)
project(week3 VERSION 1.0 LANGUAGES C CXX)

include_directories(include)
add_executable(week3_cpp src/week3.cpp)

# Set C++17 standard for the target
set_property(TARGET week3_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week3_cpp PROPERTY CXX_STANDARD_REQUIRED ON)