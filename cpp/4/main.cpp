// Uskova, chapter 8, vectors, ex. 12

#include <iostream>
#include <cstdlib>

using namespace std;

bool find(int elem, int *array, int count) {
    bool present = false;

    for (int i = 0; i < count && !present; i++) {
        if (array[i] == elem) {
            present = true;
        }
    }

    return present;
}

int main() {
    size_t n = 0;
    int *arr = nullptr;

    cout << "Array size: ";
    cin >> n;

    if (!n) {
        cerr << "Illegal size of array!" << endl;
        exit(EXIT_FAILURE);
    }

    arr = new int[n];

    cout << "Enter " << n << " elements of the array:" << endl;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int *newArr = new int[n];
    newArr[0] = arr[0];

    int count = 1;

    for (int i = 0; i < n; i++) {
        if (!find(arr[i], newArr, count)) {
            newArr[count++] = arr[i];
        }
    }

    for (int i = 0; i < count; i++) {
        cout << newArr[i] << ' ';
    }

    cout << endl;


    delete[] newArr;
    delete[] arr;

    return 0;
}
