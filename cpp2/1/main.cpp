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
//    Description:  Uskova, p. 106, ex. 20. Functions.
//        Created:  02.03.2013 11:45:53
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef bool (*predicate)(int);

int count_if(int *row, int size, predicate p)
{
    int k = 0;
    for (int i = 0; i < size; i++) {
        if (p(row[i])) {
            k++;
        }
    }

    return k;
}

bool not_in10(int a) {
    return !(a >= 0 && a <= 10);
}

int main() {
    srand(time(0));
    int n;

    cout << "Enter matrix size: ";
    cin >> n;

    int **a = new int*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];

        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 40;
            cout << a[i][j] << '\t';
        }
        cout << endl;
    }

    int *vec = new int[n];
    for (int i = 0; i < n; i++) {
        vec[i] = count_if(a[i], n, not_in10);
    }

    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << vec[i] << '\t';
    }
    
    cout << endl;
    
    delete[] vec;

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }

    delete[] a;
    return 0;
}
