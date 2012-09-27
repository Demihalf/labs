// Uskova, chapter 5, ex. 25(e)

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double x, E;
    int N;

    cout << "Input x: ";
    cin >> x;
    cout << "Input N: ";
    cin >> N;
    cout << "Input E: ";
    cin >> E;

    cout << endl;

    if (x >= -1.0 && x <= 1.0) {
        double sum = x;
        double coeff = 1.0;

        for (int i = 2; i <= N; i++) {
            coeff *= (2.0 * i - 3.0) / (2.0 * i - 2.0);
            double power = 2 * i - 1;

            double term = coeff * pow(x, power) / power;
            sum += term;
        }

        coeff = 1.0;
        double term = x;
        double sumE = 0.0;
        double sumE10 = 0.0;
        double E10 = E / 10.0;

        int kE = 0;
        int kE10 = 0;
        
        while (abs(term) > E10) {
            if (abs(term) > E) {
                sumE += term;
                kE++;
            }

            kE10++;
            sumE10 += term;

            int i = kE10 + 1;

            coeff *= (2.0 * i - 3.0) / (2.0 * i - 2.0);
            double power = 2 * i - 1;

            term = coeff * pow(x, power) / power;
        }

        double libValue = asin(x);
        cout << setprecision(30);
        cout << "Library value:\t" << libValue << endl;

        cout << "Computed value:\t" << sum << endl;
        cout << "Difference:\t" << abs(libValue - sum) << endl << endl;

        cout << "Sum of terms > E:\t" << sumE << endl;
        cout << "Difference:\t\t" << abs(libValue - sumE) << endl;
        cout << "Num of terms > E:\t" << kE << endl << endl;

        cout << "Sum of terms > E / 10:\t" << sumE10 << endl;
        cout << "Difference:\t\t" << abs(libValue - sumE10) << endl;
        cout << "Num of terms > E / 10:\t" << kE10 << endl;
    } else {
        cout << "ERROR: x must be in [-1, 1]" << endl;
        return 1;
    }

    return 0;
}
