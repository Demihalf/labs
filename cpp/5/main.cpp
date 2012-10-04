// Uskova, chapter 8, matrices, ex. 12
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

int findLargest(int *m, int rows, int cols) {
    int maximum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int curr = abs(m[i * rows + j]);
            if (curr > maximum) {
                maximum = curr;
            }
        }
    }

    return maximum;
}

int countDigits(int n) {
    int k = 0;
    int x = abs(n);

    if (!n) {
        return 1;
    }

    while (n > 0) {
        n /= 10;
        k++;
    }

    return k;
}

int main() {
    const int N = 8;
    int matrix[N][N] = {{0}};

    cout << "Enter " << N << " numbers: ";
    
    for (int i = 0; i < N; i++) {
        cin >> matrix[0][i];
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = matrix[i - 1][j] * matrix[0][j];
        }
    }

    int maxDigits = countDigits(findLargest(&matrix[0][0], N, N));
    int width = maxDigits + 2;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(width) << matrix[i][j];
        }

        cout << endl;
    }
    
    return 0;
}
