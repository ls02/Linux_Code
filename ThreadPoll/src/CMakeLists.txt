cmake_minimum_required(VERSION 3.20)

#由于上一层已经添加了项目名，这个cmake作为子节点，只需要链接当前需要的依赖即可
add_compile_options(-std=c++11 -g -O0)

set(list main.cc)

execute_process(run ${list})