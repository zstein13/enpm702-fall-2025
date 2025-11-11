cmake_minimum_required(VERSION 3.28)
project(week9 VERSION 1.0 LANGUAGES C CXX)

add_executable(week9_cpp src/main.cpp src/transportation/location.cpp src/transportation/route.cpp src/transportation/vehicle.cpp)
# add_executable(snippets_cpp src/snippets.cpp)

target_include_directories(week9_cpp PRIVATE include/transportation)

# Set C++17 standard for the targets
set_property(TARGET week9_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week9_cpp PROPERTY CXX_STANDARD_REQUIRED ON)
# set_property(TARGET snippets_cpp PROPERTY CXX_STANDARD 17)
# set_property(TARGET snippets_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

