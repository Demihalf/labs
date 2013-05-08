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
//    Description:  Uskova, p. 157, ex. 22. Files
//        Created:  02.03.2013 14:36:20
//         Author:  Valery Kharitonov, kharvd (at) gmail.com
//
// =====================================================================================

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

struct File
{
    string filename;
    string extension;
    string year;
    string month;
    string day;
};

int main() {
    ifstream catalog("files.txt");

    int length;
    catalog >> length;

    vector<File> files(length);
    for (int i = 0; i < length; i++) {
        catalog >> files[i].filename;
        catalog >> files[i].extension;
        catalog >> files[i].year;
        catalog >> files[i].month;
        catalog >> files[i].day;
    }

    vector<File> result;
    insert_iterator< vector<File> > it(result, result.begin());

    string filename;
    cin >> filename;

    copy_if(files.begin(), files.end(), it, [&](const File& a) {
            return a.filename == filename; });

    ofstream out("output.txt");

    out << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        out << result[i].filename << endl;
        out << result[i].extension << endl;
        out << result[i].year << endl;
        out << result[i].month << endl;
        out << result[i].day << endl;
    }

    return 0;
}
