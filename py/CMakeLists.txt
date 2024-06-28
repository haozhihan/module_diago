cmake_minimum_required(VERSION 3.4...3.18)
project(example_module)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 pybind11 包
# find_package(pybind11 REQUIRED)
add_subdirectory(pybind11)

# 添加库
add_library(example SHARED example.cpp)

# 添加 pybind11 模块
pybind11_add_module(example_module bindings.cpp)
target_link_libraries(example_module PRIVATE example)
