cmake_minimum_required(VERSION 3.20)
project(BlockQueue CXX)

set (list main.cc)
set (lib lpthread)

add_compile_options(-std=c++11 -g -O0 -lpthread)

add_executable(main ${list})

link_libraries(main ${lib})