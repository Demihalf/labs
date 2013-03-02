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
//    Description:  Uskova, p. 119, ex. 21. Strings.
//        Created:  02.03.2013 14:08:58
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

string convert(const string& date)
{
    string months[] = {"", "January", "February", "March",
        "April", "May", "June", "July", "August", "September",
        "October", "November", "December"};

    string month = months[atoi(date.substr(0, 2).c_str())];
    int day = atoi(date.substr(3, 2).c_str());
    int year = 1900 + atoi(date.substr(6, 2).c_str());

    ostringstream str;
    str << month << ' ' << day << ", " << year;

    return str.str();
}

int main() {
    string date;
    cin >> date;

    cout << convert(date) << endl;

    return 0;
}
