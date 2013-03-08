// =====================================================================================
// Copyright (c) 2013, Valery Kharitonov (kharvd (at) gmail.com) 
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//       Filename:  main.cpp
//    Description:  Circular list class
//        Created:  08.03.2013 21:21:21
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#ifndef _CIRCULARLIST_H
#define _CIRCULARLIST_H

#include <vector>

template<class T>
class CircularList
{
public:
    CircularList(int size, const T& init = T());
    CircularList(const std::vector<T>& initVector);
    ~CircularList();
    
    void stepLeft(int steps = 1);
    void stepRight(int steps = 1);
    T get() const;
    void set(const T& val);

private:
    void initialize(const std::vector<T>& initVector);

    struct Node
    {
        Node * prev;
        Node * next;
        T val;
    };

    Node * m_curr;
    int m_size;
};

template<class T>
CircularList<T>::CircularList(int size, const T& init)
    : m_curr(0), m_size(size)
{
    initialize(std::vector<T>(size, init));
}

template<class T>
CircularList<T>::CircularList(const std::vector<T>& initVector)
    : m_curr(0), m_size(initVector.size())
{
    initialize(initVector);
}

template<class T>
void CircularList<T>::initialize(const std::vector<T>& initVector)
{
    m_curr = new Node;
    m_curr->val = initVector[0];

    Node * node = m_curr;

    for (int i = 1; i < m_size - 1; i++) {
        Node * n = new Node;
        n->val = initVector[i];
        n->prev = node;
        
        node->next = n;
        node = n;
    }

    Node * last = new Node;
    last->val = initVector[m_size - 1];
    last->prev = node;
    last->next = m_curr;
    
    node->next = last;
    m_curr->prev = last;
}

template<class T>
CircularList<T>::~CircularList()
{
    for (int i = 0; i < m_size; i++) {
        Node * n = m_curr;
        m_curr = m_curr->next;
        delete n;
    }
}

template<class T>
void CircularList<T>::stepLeft(int steps)
{
    for (int i = 0; i < steps; i++)
        m_curr = m_curr->prev;
}

template<class T>
void CircularList<T>::stepRight(int steps)
{
    for (int i = 0; i < steps; i++)
        m_curr = m_curr->next;
}

template<class T>
T CircularList<T>::get() const
{
    return m_curr->val;    
}

template<class T>
void CircularList<T>::set(const T& val)
{
    m_curr->val = val;
}

#endif
