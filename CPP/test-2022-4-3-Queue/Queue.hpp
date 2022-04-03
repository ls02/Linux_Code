#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__
#include <iostream>
#include <deque>

namespace ls
{
    template<class T, class Container = std::deque<T> >
    class queue
    {
    private:
        Container _con;
    public:
        void push(const T& val)
        {
            _con.push_back(val);
        }

        void pop(void)
        {
            _con.pop_front();
        }

        T& front(void)
        {
            return _con.front();
        }

        T& back(void)
        {
            return _con.back();
        }

        size_t size(void)
        {
            return _con.size();
        }

        bool empty(void)
        {
            return _con.size() == 0;
        }
    };
}

#endif
