cmake_minimum_required(VERSION 3.20)
project(cpp_example)

set(CMAKE_CXX_STANDARD 11)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRC 变量
aux_source_directory(. DIR_SRC)

add_executable(cpp_example src/main.cpp)
