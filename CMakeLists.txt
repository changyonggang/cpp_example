cmake_minimum_required(VERSION 3.20)
project(cpp_example)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_example main.cpp AtomicClass.cpp AtomicClass.h)
