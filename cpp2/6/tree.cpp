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
//       Filename:  tree.cpp
//    Description:  Binary tree structure definition
//        Created:  03.03.2013 10:26:55
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include "tree.h"

#include <iostream>

Tree * new_tree(Tree * left, Tree * right, char val)
{
    Tree * t = new Tree;
    t->left = left;
    t->right = right;
    t->val = val;

    return t;
}

Tree * duplicate_tree(const Tree * src)
{
    if (!src) return NULL;

    return new_tree(duplicate_tree(src->left), 
            duplicate_tree(src->right), src->val);
}

void print_branch(const Tree * t, int offset)
{
    if (!t) return;

    for (int i = 0; i < offset + 1; i++) {
        std::cout << "| ";
    }

    std::cout << std::endl;

    for (int i = 0; i < offset; i++) {
        std::cout << "| ";
    }

    std::cout << "+-";

    print_tree(t, offset + 1);
}

void print_tree(const Tree * t, int offset)
{
    if (!t) return;

    std::cout << t->val << std::endl;

    print_branch(t->left, offset);
    print_branch(t->right, offset);
}

void delete_tree(Tree * t) 
{
    if (!t) return;

    if (t->left) delete_tree(t->left);
    if (t->right) delete_tree(t->right);

    delete t;
}
