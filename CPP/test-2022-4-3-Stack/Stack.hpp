#ifndef __STACK_HPP__
#define __STACK_HPP__ 
#include <iostream>
#include <deque>

namespace ls 
{
    template<class T, class Container = std::deque<T> >
    class stack
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
            _con.pop_back();
        }

        T& top(void)
        {
            return _con.back();
        }

        size_t size(void)const
        {
            return _con.size();
        }

        bool empty(void)const
        {
            return _con.size() == 0;
        }
    };
}

#endif
