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
//    Description:  Uskova, p. 163, ex. 2. Circular list.
//        Created:  08.03.2013 21:21:21
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "circularlist.h"

using namespace std;

int getSize(CircularList<int>& l)
{
    int initial = l.get();

    while (true) {
        l.stepRight();
        int steps = 1;

        while (l.get() != initial) {
            l.stepRight();
            steps++;
        }
        
        l.set((l.get() + 1) % 1001);
        l.stepLeft(steps);

        if (l.get() != initial) {
            return steps;
        }
    }
}

int main()
{
    srand(time(0));

    vector<int> initVector(rand() % 500 + 1);
    for (int i = 0; i < initVector.size(); i++) {
        initVector[i] = rand() % 25;
    }

    CircularList<int> list(initVector);

    cout << "Guessed size: " << getSize(list) << endl;
    cout << "Real size: " << initVector.size() << endl;

    return 0;
}
