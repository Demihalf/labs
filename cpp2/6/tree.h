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
//       Filename:  expression.cpp
//    Description:  Binary tree structure declaration
//        Created:  03.03.2013 10:18:07
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#ifndef _TREE_H
#define _TREE_H

#include <cstdlib>

struct Tree
{
    Tree *left;
    Tree *right;
    char val;  
};


// Allocates memory for a new tree element and sets references
Tree * new_tree(Tree * left = NULL, 
        Tree * right = NULL, char val = 0);

// Deep copies the whole tree
Tree * duplicate_tree(const Tree * src);

// Prints the tree
void print_tree(const Tree * t, int offset = 0);

// Deletes tree and both its subtrees recursively
void delete_tree(Tree * t);

#endif
