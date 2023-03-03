#ifndef __BLOCK_QUEUE_HPP__
#define __BLOCK_QUEUE_HPP__

#include <iostream>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

namespace ls
{
    const int defcap = 5;
    template<class T>
    class BlockQueue 
    {
        private:
            int _cap; //容量
            std::queue<T> _bq; //交易场所
            pthread_mutex_t mtx;
            pthread_cond_t _full; //满的消费者在该条件变量下等待
            pthread_cond_t _empty; //空的生产者在该条件变量下等待

        private:
            bool IsFull()
            {
                return _bq.size() == _cap;
            }

            bool IsEmpty()
            {
                return _bq.size() == 0;
            }
        public:
            BlockQueue(int cap = defcap)
                :_cap(cap)
            {
                pthread_mutex_init(&mtx, nullptr);
                pthread_cond_init(&_full, nullptr);
                pthread_cond_init(&_empty, nullptr);
            }

            ~BlockQueue()
            {
                pthread_mutex_destroy(&mtx);
                pthread_cond_destroy(&_full);
                pthread_cond_destroy(&_empty);
            }

            void Lock()
            {
                pthread_mutex_lock(&mtx);
            }

            void UnLock()
            {
                pthread_mutex_unlock(&mtx);
            }

            void ProducerWait()
            {
                pthread_cond_wait(&_full, &mtx);
            }

            void ConsumerWait()
            {

                pthread_cond_wait(&_empty, &mtx);
            }

            void ProducerWakeUp()
            {
                pthread_cond_signal(&_full); 
            }

            void ConsumerWakeUp()
            {
                pthread_cond_signal(&_empty);
            }

            //生产者生产数据
            void Push(const T& in)
            {
                Lock();
                //如果生产者满了停止生产
                while (IsFull())
                {
                    ProducerWait();
                }
                _bq.push(in);
                UnLock();
                ConsumerWakeUp();
            }


            //消费者消费数据
            void Pop(T* out)
            {
                Lock();
                while (IsEmpty())
                {
                    ConsumerWait();
                }
                *out = _bq.front();
                _bq.pop();
                UnLock();
                ProducerWakeUp();
            }
    };
}

#endif
