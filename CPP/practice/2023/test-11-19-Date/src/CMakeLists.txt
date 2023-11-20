CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

add_compile_options(-std=c++11 -g)

set(list main.cc)

add_executable(
  run
  ${list}
  )
