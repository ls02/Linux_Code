cmake_minimum_required(VERSION 3.20) 

add_compile_options(-std=c++11 -g -O0 -std=c++14)

set(TcpList Socket.cc TCPSocket.cc)
set(EpollList Epoll.cc EpollServer.cc)

set(list main.cc ${TcpList} ${EpollList})

add_executable(run ${list})