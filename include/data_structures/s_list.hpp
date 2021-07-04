/*
MIT License

Copyright (c) 2021 Max A. Jurankov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file
 * @brief Singly-linked list implementation
 * @author [astronmax](https://github.com/astronmax)
 */

#pragma once

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

/**
 * @brief General namespace of algorithms library
 */
namespace alg {

/**
 * @brief Container implemented as singly-linked list
 */
template <class T>
class s_list {

public:
    /**
     * @brief Structure of s_list nodes
     */
    struct node {

        /**
         * @brief Constructor without parameters
         */
        node()
            : m_next(nullptr)
        {
        }

        /**
         * @brief Constructor that initialize data of the node with value from parameter
         */
        node(T data, std::shared_ptr<node> next = nullptr)
            : m_data(data)
            , m_next(next)
        {
        }

        /**
         * @brief Method to get value of the node
         * @return data of the node
         */
        auto& get()
        {
            if (this == static_cast<node*>(nullptr))
                throw std::logic_error("Can't get value of node that isn't initialized");

            return m_data;
        }

        /**
         * @brief Method to get pointer to the next node
         * @return pointer to the next node
         */
        auto& next()
        {
            if (this == static_cast<node*>(nullptr))
                throw std::logic_error("Can't get next node of node that isn't initialized");

            return m_next;
        }

    private:
        T m_data; // value of node
        std::shared_ptr<node> m_next; // pointer to next node

    }; // struct node

public:
    /**
     * @brief Structure of custom forward iterator.
     * Needed to provide the ability to interact with a sequence of 
     * values stored in a s_list.
     */
    struct iterator {

        // some tags for compatible with STL
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = std::shared_ptr<node>;
        using reference = T&;

        /**
         * @brief Constructor without parameters
         */
        iterator()
            : m_ptr(nullptr)
        {
        }

        /**
         * @brief Constructor that initialize iterator
         */
        iterator(pointer ptr)
            : m_ptr(ptr)
        {
        }

        // overloading of operator * (return value of node)
        reference operator*() const { return m_ptr->get(); }

        // overloading of operator -> (return shared pointer to node)
        pointer operator->() const { return m_ptr; }

        // overloading of prefix operator ++
        iterator& operator++()
        {
            m_ptr = m_ptr->next();
            return *this;
        }

        // overloading of postfix operator ++
        iterator operator++(int)
        {
            iterator it { *this };
            m_ptr = m_ptr->next();
            return it;
        }

        // overloading of comparsion operators
        friend bool operator==(const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };

        friend bool operator<(const iterator& a, const iterator& b) { return a.m_ptr < b.m_ptr; };
        friend bool operator<=(const iterator& a, const iterator& b) { return a.m_ptr <= b.m_ptr; };

        friend bool operator>(const iterator& a, const iterator& b) { return a.m_ptr > b.m_ptr; };
        friend bool operator>=(const iterator& a, const iterator& b) { return a.m_ptr >= b.m_ptr; };

    private:
        pointer m_ptr; // shared pointer to the node

    }; // struct forward_iterator

private:
    std::shared_ptr<node> m_first; // pointer to the beginning of list
    std::shared_ptr<node> m_last; // pointer to the ending of list
    std::size_t m_size; // size of list (count of elements)

public:
    /**
     * @brief Constructor without parameters
     */
    s_list()
    {
        m_first = std::make_shared<node>();
        m_last = nullptr;
        m_size = 0;
    }

    /**
     * @brief Constructor for variable count of parameters.
     * Called when an object initialize with initializer s_list
     */
    s_list(std::initializer_list<T> args)
        : s_list()
    {
        for (auto item : args)
            push_back(item);
    }

    /**
     * @brief Destructor. Call clear() and delete first node
     */
    ~s_list()
    {
        clear();
        m_first.reset();
    }

    /**
     * @brief Method to check if s_list is empty
     * @return 1 if empty; 0 if it's not
     */
    auto empty() const noexcept { return (m_last == nullptr); }

    /**
     * @brief Method to find node with needed value in s_list
     * @param item value of needed node
     * @return shared pointer to node with needed value
     */
    auto find(const T item) -> std::shared_ptr<node>
    {
        if (empty())
            throw std::logic_error("Nothing to find: list is empty");

        // try to find node in list
        auto t = m_first;
        for (; t != m_last && t->next()->get() != item; t = t->next())
            ;

        // node not found
        if (t == m_last)
            return nullptr;

        // sought node - next node after t
        return t->next();
    }

    /**
     * @brief Method to add node at the ending of the s_list
     * @param item value of the node to be added
     */
    auto push_back(const T item)
    {
        if (empty()) {
            m_first->next() = std::make_shared<node>(item);
            m_last = m_first->next();
            m_last->next() = nullptr;
        } else {
            m_last->next() = std::make_shared<node>(item);
            m_last = m_last->next();
            m_last->next() = nullptr;
        }

        m_size++;
    }

    /**
     * @brief Method to add node at the beginning of the s_list
     * @param item value of the node to be added
     */
    auto push_front(const T item)
    {
        if (empty()) {
            m_first->next() = std::make_shared<node>(item);
            m_last = m_first->next();
            // nullptr - end of the list
            m_last->next() = nullptr;
        } else {
            auto tmp = std::make_shared<node>(item);
            tmp->next() = m_first->next();
            m_first->next() = tmp;
            // nullptr - end of the list
            m_last->next() = nullptr;
        }

        m_size++;
    }

    /**
     * @brief Method to delete node with needed value from s_list
     * @param item value of the node to be deleted
     */
    auto erase(const T item)
    {
        if (empty())
            throw std::logic_error("Can't make erase: list is empty");

        // try to find needed node
        auto t = m_first;
        std::shared_ptr<node> to_be_removed = nullptr;

        for (; t != m_last && t->next()->get() != item; t = t->next())
            ;

        // node not found
        if (t == m_last)
            throw std::invalid_argument("Can't make erase: element not found");

        // delete node
        to_be_removed = t->next();
        t->next() = t->next()->next();
        to_be_removed.reset();

        // deleted node - last node
        if (t->next() == nullptr)
            // now last node is t
            m_last = t;

        // last node has been deleted
        if (m_first == m_last)
            // list is empty now
            m_last = nullptr;

        m_size--;
    };

    /**
     * @brief Method to insert node with needed value after some node
     * @param pos node value after which you want to insert a new node
     * @param item value of the node to be added
     */
    auto insert_after(const T pos, const T item)
    {
        if (empty())
            throw std::logic_error("Can't make insert after something: list is empty");

        // try to find previous node
        auto prev = m_first;
        for (; prev != m_last && prev->next()->get() != pos; prev = prev->next())
            ;

        // previous node not found
        if (prev == m_last)
            throw std::invalid_argument("Can't find previous item in list for insert after it");

        // real previous node is next node of prev
        prev = prev->next();
        auto new_node = std::make_shared<node>(item);

        // need to insert a node at the end of the list
        if (prev == m_last) {
            // make push_back with not empty list
            m_last->next() = new_node;
            m_last = m_last->next();
            m_last->next() = nullptr;
        } else {
            auto tmp = prev->next();
            prev->next() = new_node;
            new_node->next() = tmp;
        }

        m_size++;
    }

    /**
     * @brief Method to delete all nodes in s_list except the first node
     */
    auto clear()
    {
        std::shared_ptr<node> ptr;
        // nullptr - end of the list
        while (m_first->next() != nullptr) {
            // make erase of current node
            ptr = m_first->next();
            m_first->next() = m_first->next()->next();
            ptr.reset();
        }

        // list is empty if last node is null pointer and size is 0
        m_last.reset();
        m_size = 0;
    }

    /**
     * @brief Method to get size of s_list
     * @return size of s_list
     */
    auto size() const
    {
        return m_size;
    }

    /**
     * @brief Method to get first element in the s_list
     * @return reference to value of node after first node
     */
    auto& front() const
    {
        if (empty())
            throw std::logic_error("List is empty");

        return m_first->next()->get();
    }

    /**
     * @brief Method to get last element in the s_list
     * @return reference fo value of last node
     */
    auto& back() const
    {
        if (empty())
            throw std::logic_error("List is empty");

        return m_last->get();
    }

    /**
     * @brief Method to get iterator to the first element of the s_list
     * @return iterator to the first element of the s_list
     */
    auto begin() const
    {
        iterator it { m_first->next() };
        return it;
    }

    /**
     * @brief Method to get iterator to the element following the last element of the s_list
     * @return iterator to the element following the last element of the s_list
     */
    auto end() const
    {
        iterator it { m_last->next() };
        return it;
    }

}; // class s_list

}; // namespace alg

/**
 * @brief Overloading of operator << for s_list
 */
template <typename T>
std::ostream& operator<<(std::ostream& s, const alg::s_list<T>& v)
{
    for (const auto& e : v) {
        s << e << " ";
    }
    return s;
}