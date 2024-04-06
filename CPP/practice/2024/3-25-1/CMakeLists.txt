cmake_minimum_required(VERSION 3.20)

project(test CXX)

set (list main.cc)

add_compile_options(-std=c++11 -g -O0)

add_executable(main ${list})

target_link_libraries(main yaml-cpp)