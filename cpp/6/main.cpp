// Uskova, Chapter 12, exercise 14
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

typedef uint8 GroupNumber;
typedef uint8 Mark;

const int MAX_GROUPS = 7;
const int SUBJECTS_COUNT = 3;
enum Subject { FUNC_ANALYSIS = 0, NUMERICAL_METHODS, ECONOMICS };
const char * SUBJECT_NAMES[] = { "Functional analysis", "Numerical methods",
    "Economics" };

struct Student {
    string lastName;
    GroupNumber groupNumber;
    Mark marks[SUBJECTS_COUNT];
};

bool isSatisfactory(Mark m);
bool isGood(Mark m);

vector<Student> inputStudents(int n);

void printFailed(const vector<Student>& students);
int countGoodStudents(const vector<Student>& students);
int bestSubject(const vector<Student>& students);
vector<pair<GroupNumber, double>> groupsPerformance(const vector<Student>&
        students);

int main() {
    int n;
//     cout << "Number of students: ";
    cin >> n;

    vector<Student> students(inputStudents(n));

    printFailed(students);
    cout << "Good students: " << countGoodStudents(students) /
        static_cast<double>(n) * 100 << "%\n";
    cout << "Best subject: " << SUBJECT_NAMES[bestSubject(students)] << endl;

    vector<pair<GroupNumber, double>>
        groupsAverage(groupsPerformance(students));
    sort(begin(groupsAverage), end(groupsAverage),
        [](pair<GroupNumber, double> x, pair<GroupNumber, double> y) {
            return x.second > y.second;
        });


    cout << "Groups rating: " << endl;

    for (auto gr : groupsAverage) {
        cout << gr.first << ": " << gr.second << endl;
    }

    return 0;
}

bool isSatisfactory(Mark m) {
    return (m >= 3);
}

bool isGood(Mark m) {
    return (m >= 4);
}

vector<Student> inputStudents(int n) {
    vector<Student> students(n);
    for (auto &st : students) {
//         cout << "Last name: ";
        cin >> st.lastName;
//         cout << "Group: ";
        cin >> st.groupNumber;
//         cout << "Functional analysis mark: ";
        cin >> st.marks[FUNC_ANALYSIS];
//         cout << "Numerical methods mark: ";
        cin >> st.marks[NUMERICAL_METHODS];
//         cout << "Economics mark: ";
        cin >> st.marks[ECONOMICS];

//         cout << endl;
    }

    return students;
}

void printFailed(const vector<Student>& students) {
    cout << "FAIL: " << endl;

    for (auto st : students) {
        for (auto mark : st.marks) {
            if (!isSatisfactory(mark)) {
                cout << st.lastName << endl;
                break;
            }
        }
    }

    cout << endl;
}

int countGoodStudents(const vector<Student>& students) {
    int k = 0;

    for (auto st : students) {
        bool good = true;
        for (auto mark : st.marks) {
            if (!isGood(mark)) {
                good = false;
                break;
            }
        }

        if (good) {
            k++;
        }
    }

    return k;
}

int bestSubject(const vector<Student>& students) {
    Mark subjMarksSum[SUBJECTS_COUNT];

    for (auto st : students) {
        for (int i = 0; i < SUBJECTS_COUNT; i++) {
            subjMarksSum[i] += st.marks[i];
        }
    }

    int bestI = 0;
    for (int i = 1; i < SUBJECTS_COUNT; i++) {
        if (subjMarksSum[i] > subjMarksSum[bestI]) {
            bestI = i;
        }
    }

    return bestI;
}

vector<pair<GroupNumber, double>> groupsPerformance(const vector<Student>&
        students) {
    vector<double> groupsSums(MAX_GROUPS, 0.0);
    vector<int> studCount(MAX_GROUPS, 0);

    for (auto st : students) {
        for (auto mark : st.marks) {
            groupsSums[st.groupNumber - 1] += mark;
        }

        studCount[st.groupNumber - 1]++;
    }

    vector<pair<GroupNumber, double>> groups;
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (groupsSums[i] != 0.0) {
            pair<GroupNumber, double> gr;
            gr.first = i + 1;
            gr.second = groupsSums[i] / (studCount[i] * SUBJECTS_COUNT);
            groups.push_back(gr);
        }
    }

    return groups;
}


