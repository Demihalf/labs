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
//    Description:  Uskova, p. 112, ex. 5. Recursion.
//        Created:  02.03.2013 12:20:36
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1e-5;

double y_n(double x, int n, int k) {
    if (n == 0) 
        return 1;

    double y_n_1 = y_n(x, n - 1, k);
    return y_n_1 + (x / pow(y_n_1, k - 1) - y_n_1) / k;
}

double my_root(double x, int k) {
    int n = 1;
    double y1 = y_n(x, 0, k);
    double y2 = y_n(x, 1, k);

    while (abs(y2 - y1) > EPS) {
        n++;
        y1 = y2;
        y2 = y_n(x, n, k);
    }    

    return y2;
}

int main() {
    double a;
    cout << "Enter a: ";
    cin >> a;

    cout << (my_root(a, 3) - my_root(a * a + 1, 6)) / (1 + my_root(3 + a, 7));
    
    return 0;
}
