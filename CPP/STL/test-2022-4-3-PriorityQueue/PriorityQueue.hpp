#ifndef __PRIORITY_QUEUE_HPP__
#define __PRIORITY_QUEUE_HPP__
#include <vector>
#include <iostream>

namespace ls
{
    template<class T >
    struct less
    {
        bool operator()(const T& l, const T& r) const
        {
            return l < r;
        }
    };

    template<class T, class Container = std::vector<T>,\
            class Compare = less<typename Container::value_type> > 
    class PriorityQueue
    {
    private:
        Container _con;

        void UpAdjusted(size_t child)
        {
            size_t parent = (child - 1) / 2;
            
            while (child > 0)
            {
                if (Compare()(_con[parent], _con[child]))
                {
                    std::swap(_con[parent], _con[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }

        void DownAdjusted(size_t parent)
        {
            size_t child = parent * 2 + 1;

            while (child < size())
            {
                if (child + 1 < size() && Compare()(_con[child], _con[child + 1]))
                {
                    child++;
                }

                if (Compare()(_con[parent], _con[child]))
                {
                    std::swap(_con[parent], _con[child]);
                    
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                {
                    break;
                }
            }
        }
    public:
        void push(const T& val)
        {
            _con.push_back(val);
            UpAdjusted(size() - 1);
        }

        void pop(void)
        {
            std::swap(_con[0], _con[size() - 1]);
            _con.pop_back();

            DownAdjusted(0);
        }
        
        T& top(void)
        {
            return _con[0];
        }

        bool empty(void) const
        {
            return size() == 0;
        }

        size_t size()const
        {
            return _con.size();
        }
    };
}
#endif
