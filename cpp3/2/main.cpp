#include <fstream>
#include <queue>
#include <cstdlib>
using namespace std;

int main() {
    ifstream in("in.txt");
    ofstream out("out.txt");

    string line;

    while (getline(in, line)) {
        queue<char> digs;
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                digs.push(line[i]);
            } else {
                out << line[i];
            }
        }

        while (!digs.empty()) {
            out << digs.front();
            digs.pop();
        }

        out << endl;
    }

    return 0;
}
