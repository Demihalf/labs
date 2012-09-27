// Uskova, chapter 6, ex. 19

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<char>> text;

    char c;
    vector<char> buffer;
    
    cin.get(c);
    buffer.push_back(c);
    bool in_word = isalpha(c);

    while (cin.get(c)) {
        if ((in_word && !isalpha(c)) || (!in_word && isalpha(c))) {
            text.push_back(buffer);
            buffer.clear();

            in_word = !in_word;
        }

        buffer.push_back(c);
    }

    text.push_back(buffer);

    for (auto &word : text)  {
        if (isalpha(word[0])) {
            word[0] = toupper(word[0]);
        }
    }
    
    for (auto word : text)  {
        for (auto c : word) {
            cout << c;
        }
    }

    return 0;
}
