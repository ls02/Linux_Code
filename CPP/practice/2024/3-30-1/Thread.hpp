/*
 * @Author: ls02 liangson02@163.com
 * @Date: 2024-03-31 10:03:01
 * @LastEditors: ls02 liangson02@163.com
 * @LastEditTime: 2024-03-31 10:33:05
 * @FilePath: /practice/2024/3-30-1/Thread.hpp
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <pthread.h>

#include <iostream>
#include <string>

typedef void* (*callback_t)(void*);

static int num = 1;

class Thread {
    // 为什么要定义成静态的？因为C语言没有类的概念，我们要兼容
    // pthreadCreate库的参数
    // 而在类里面定义成static成员这样既满足了C语言的接口也满足了与类保持关联
    static void* Routine(void* args) {
        Thread* thread = static_cast<Thread*>(args);
        thread->Run();

        return nullptr;
    }

   public:
    Thread(callback_t start_routine, void* args)
        : _start_routine(start_routine), _args(args) {}

    void Start() {
        _name = "Thread-";
        _name += std::to_string(num++);

        pthread_create(&tid, nullptr, Routine, this);
    }

    void Run() { _start_routine(_args); }

    void Join() { pthread_join(tid, nullptr); }

    ~Thread() { Join(); }

    std ::string Nmae() { return _name; }

   private:
    pthread_t tid;
    void* _args;
    callback_t _start_routine;
    std::string _name;
};

#endif