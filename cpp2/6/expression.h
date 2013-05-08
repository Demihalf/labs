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

#ifndef _EXPRESSION_H
#define _EXPRESSION_N

#include <string>
#include <sstream>

#include "tree.h"

using std::string;

class Expression
{
public:
    Expression(); // Empty expression
    Expression(const string& str); // Build expression from a string
    ~Expression();

    string getString() const; // Get string representation of the expression

    Expression simplify() const;
    Expression derive(char var) const;
    void printTree() const {
        print_tree(m_head);
    }
    
private:
    string toRPN(const string& expr) const;
    bool isop(char c) const;
    bool isterminal(char c) const;
    Tree * treeFromRPN(const string& rpn);
    Tree * derivative(const Tree * expr, char var) const;
    Tree * simplifyTree(Tree * expr) const;
    void buildFormula(std::ostringstream& str, const Tree * expr) const;

private:
    Tree * m_head;

    int m_rpnOffset;
};

#endif
