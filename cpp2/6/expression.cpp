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
//    Description:  Expression class for ex. 6
//        Created:  03.03.2013 10:18:07
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include "expression.h"

#include <cstdlib>
#include <algorithm>
#include <stack>

#include "tree.h"

Expression::Expression()
    : m_head(NULL), m_rpnOffset(0)
{
}

Expression::Expression(const string& str)
    : m_rpnOffset(0)
{
    string rpn = toRPN(str);
    std::reverse(rpn.begin(), rpn.end());
    
    m_head = treeFromRPN(rpn);
}

Expression::~Expression()
{
    delete_tree(m_head);
}

string Expression::toRPN(const string& expr) const
{
    string res;
    std::stack<char> st;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (c == '(' || isop(c)) {
            st.push(c);
        } else if (isterminal(c)) {
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

bool Expression::isop(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool Expression::isterminal(char c) const
{
    return (isdigit(c) || isalpha(c));
}

Tree * Expression::treeFromRPN(const string& rpn)
{
    Tree * t = new_tree(NULL, NULL, rpn[m_rpnOffset]);
    m_rpnOffset++;

    if (m_rpnOffset < rpn.length()) {
        if (isterminal(rpn[m_rpnOffset])) {
            t->right = new_tree(NULL, NULL, rpn[m_rpnOffset]);
            m_rpnOffset++;
        } else {
            t->right = treeFromRPN(rpn);
        }
    }

    if (m_rpnOffset < rpn.length()) {
        if (isterminal(rpn[m_rpnOffset])) {
            t->left = new_tree(NULL, NULL, rpn[m_rpnOffset]);
            m_rpnOffset++;
        } else {
            t->left = treeFromRPN(rpn);
        }
    }

    return t;
}

Tree * Expression::derivative(const Tree * expr, char var) const
{
    if (!expr)
        return NULL;

    if (expr->val == var) {
        return new_tree(NULL, NULL, '1');
    }

    if (isterminal(expr->val)) {
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

Tree * Expression::simplifyTree(Tree * expr) const
{
    if (!expr) return NULL;

    if (isterminal(expr->val)) 
        return new_tree(NULL, NULL, expr->val);

    if ((expr->val == '+' && expr->left->val == '0') ||
        (expr->val == '*' && expr->left->val == '1'))
    {
        return simplifyTree(expr->right);
    }

    if (((expr->val == '+' || expr->val == '-') && expr->right->val == '0') ||
        (expr->val == '*' && expr->right->val == '1'))
    {
        return simplifyTree(expr->left);
    }

    if (expr->val == '*' && (expr->left->val == '0' || expr->right->val == '0')) {
        return new_tree(NULL, NULL, '0');
    }

    Tree * new_left = simplifyTree(expr->left);
    Tree * new_right = simplifyTree(expr->right);

    return new_tree(new_left, new_right, expr->val);
}

void Expression::buildFormula(std::ostringstream& str, const Tree * t) const
{
    if (!t) return;

    if (isterminal(t->val)) {
        str << t->val;
        return;
    }

    str << '(';
    buildFormula(str, t->left);
    str << t->val;
    buildFormula(str, t->right);
    str << ')';
}

Expression Expression::derive(char var) const
{
    Expression expr;
    expr.m_head = derivative(m_head, var);

    return expr;
}

Expression Expression::simplify() const
{
    Expression simple;
    simple.m_head = simplifyTree(m_head);

    return simple;
}

string Expression::getString() const
{
    std::ostringstream str;
    buildFormula(str, m_head);

    return str.str();
}

