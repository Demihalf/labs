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
//    Description:  Uskova, p. 164, ex. 11g. Binary trees.
//        Created:  02.03.2013 21:04:51
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdlib>
using namespace std;

struct Tree
{
    Tree *left;
    Tree *right;
    char val;  
};

bool isop(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string to_RPN(const string& expr)
{
    string res;
    stack<char> st;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (c == '(' || isop(c)) {
            st.push(c);
        } else if (isdigit(c) || isalpha(c)) {
            res.push_back(c);
        } else {
            while (!st.empty() && st.top() != '(') {
                res.push_back(st.top());
                st.pop();
            }

            if (!st.empty()) {
                st.pop();
            }
        }
    }

    return res;
}

Tree * new_tree(Tree * left = NULL, Tree * right = NULL, char val = 0)
{
    Tree * t = new Tree;
    t->left = left;
    t->right = right;
    t->val = val;

    return t;
}

Tree * duplicate_tree(Tree * src)
{
    if (!src) {
        return NULL;
    }

    return new_tree(duplicate_tree(src->left), 
            duplicate_tree(src->right), src->val);
}

pair<Tree *, int> tree_gen(const string& rpn, int offset = 0)
{
    Tree * t = new_tree(NULL, NULL, rpn[offset]);
    offset++;

    if (offset < rpn.length()) {
        if (isdigit(rpn[offset]) || isalpha(rpn[offset])) {
            t->right = new_tree(NULL, NULL, rpn[offset]);
            offset++;
        } else {
            pair<Tree *, int> res = tree_gen(rpn, offset);
            t->right = res.first;
            offset = res.second;
        }
    }

    if (offset < rpn.length()) {
        if (offset < rpn.length() && isdigit(rpn[offset]) || isalpha(rpn[offset])) {
            t->left = new_tree(NULL, NULL, rpn[offset]);
            offset++;
        } else {
            pair<Tree *, int> res = tree_gen(rpn, offset);
            t->left = res.first;
            offset = res.second;
        }
    }


    pair<Tree *, int> res;
    res.first = t;
    res.second = offset;

    return res;
}

void print_tree(Tree * t, int offset);

void print_branch(Tree * t, int offset)
{
    if (!t) {
        return;
    }

    for (int i = 0; i < offset + 1; i++) {
        cout << "| ";
    }

    cout << endl;

    for (int i = 0; i < offset; i++) {
        cout << "| ";
    }

    cout << "+-";

    print_tree(t, offset + 1);
}

void print_tree(Tree * t, int offset = 0)
{
    if (!t) {
        return;
    }

    cout << t->val << endl;

    print_branch(t->left, offset);
    print_branch(t->right, offset);
}

void delete_tree(Tree * t) {
    if (!t)
        return;

    if (t->left) {
        delete_tree(t->left);
    }

    if (t->right) {
        delete_tree(t->right);
    }

    delete t;
}

Tree * derivative(Tree * expr, char var)
{
    if (!expr)
        return NULL;

    if (expr->val == var) {
        return new_tree(NULL, NULL, '1');
    }

    if (isdigit(expr->val) || isalpha(expr->val)) {
        return new_tree(NULL, NULL, '0');
    }

    if (expr->val == '+' || expr->val == '-') {
        Tree * left = derivative(expr->left, var);
        Tree * right = derivative(expr->right, var);
        
        return new_tree(left, right, expr->val);
    }

    Tree * left_derivative = derivative(expr->left, var);
    Tree * right_derivative = derivative(expr->right, var);
    Tree * left = duplicate_tree(expr->left);
    Tree * right = duplicate_tree(expr->right);

    Tree * first = new_tree(left_derivative, right, '*');
    Tree * second = new_tree(left, right_derivative, '*');

    if (expr->val == '*') {
        return new_tree(first, second, '+');
    } else {
        Tree * numerator = new_tree(first, second, '-');
        Tree * denominator = new_tree(duplicate_tree(right), duplicate_tree(right), '*');

        return new_tree(numerator, denominator, '/');
    }
}

int main() 
{
    string expr;
    cin >> expr;

    string rpn = to_RPN(expr);
    reverse(rpn.begin(), rpn.end());

    Tree * tree = tree_gen(rpn).first;
    print_tree(tree);

    cout << endl;

    Tree * deriv = derivative(tree, 'x');
    print_tree(deriv);

    delete_tree(deriv);
    delete_tree(tree);
    
    return 0;
}
