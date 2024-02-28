#ifndef __MY_LIST_HPP__
#define __MY_LIST_HPP__

#include <iostream>

template <class T>
struct list_node {
    list_node(const T &val) : _next(nullptr), _prev(nullptr), _val(val) {}

    list_node<T> *_next;
    list_node<T> *_prev;
    T _val;
};

template <class T, class Ref, class Ptr>
struct __list_iterator {
    typedef __list_iterator<T, Ref, Ptr> self;
    typedef list_node<T> Node;

    __list_iterator(Node *node) : _node(node) {}

    self &operator++() {
        _node = _node->_next;
        return *this;
    }

    self &operator--() {
        _node = _node->_prev;
        return *this;
    }

    self operator--(int) {
        self tmp = *this;
        _node = _node->_prev;

        return tmp;
    }
    /* Ptr operator->() { &(operator*()); } */
    Ptr operator->() { &_node->_val; }

    bool operator!=(const self &node) { return _node != node._node; }

    Ref operator*() { return _node->_val; }

    Node *_node;
};

template <class T>
class list {
    typedef list_node<T> Node;

   public:
    typedef __list_iterator<T, T &, T *> iterator;
    typedef __list_iterator<const T, const T &, const T *> const_iterator;

    list(const T &val = T()) {
        _head = new Node(val);
        _head->_prev = _head;
        _head->_next = _head;
        _size = 0;
    }

    void push_back(const T &val) {
        /* Node *new_node = new Node(val); */
        /* Node *tail = _head->_prev; */
        /* new_node->_prev = tail; */
        /* new_node->_next = _head; */
        /* _head->_prev = new_node; */
        /* tail->_next = new_node; */
        /* _size++; */

        insert(end(), val);
    }

    iterator insert(iterator pos, const T &val) {
        Node *new_node = new Node(val);
        Node *cur = pos._node;
        Node *prev = cur->_prev;
        cur->_prev = new_node;
        prev->_next = new_node;
        new_node->_prev = prev;
        new_node->_next = cur;
        _size++;

        return new_node;
    }

    iterator erase(iterator pos) {
        // 这个检查的作用是防止他全删掉
        if (pos._node == end()) {
            return _head;
        }

        Node *cur = pos._node;
        Node *prev = cur->_prev;
        Node *next = cur->_next;
        prev->_next = next;
        next->_prev = prev;

        delete cur;
        _size--;

        return next;
    }

    void pop_back() { erase(--end()); }

    size_t size() const { return _size; }

    iterator begin() { return iterator(_head->_next); }
    const_iterator begin() const { return const_iterator(_head->_next); }

    iterator end() { return iterator(_head); }
    const_iterator end() const { return const_iterator(_head); }

   private:
    Node *_head;
    size_t _size;
};

#endif  // !__MY_LIST_HPP__
