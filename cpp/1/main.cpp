// Uskova, chapter 4, ex. 11

#include <iostream>
#include <cmath>

using namespace std;

struct Point
{
    double x;
    double y;
};

double sqr(double x) 
{
	return x * x;
}

double pointsDistance(Point p1, Point p2)
{
    return sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y, 2.0));
}

bool fuzzyEqual(double x, double y, double eps)
{
    return (abs(x - y) < eps);
}

int main()
{
    Point a, b, c;

    cout << "Enter x1: ";
    cin >> a.x;

    cout << "Enter y1: ";
    cin >> a.y;
    
    cout << "Enter x2: ";
    cin >> b.x;

    cout << "Enter y2: ";
    cin >> b.y;

    cout << "Enter x3: ";
    cin >> c.x;

    cout << "Enter y3: ";
    cin >> c.y;

    double sideA = pointsDistance(a, b),
           sideB = pointsDistance(b, c),
           sideC = pointsDistance(a, c);

    const double eps = 1e-5;

    if (sideA > eps && sideB > eps && sideC > eps) {
        // Law of cosines
        double angleACos = (sqr(sideB) + sqr(sideC) - sqr(sideA)) / 2.0 / sideB 
                                                                  / sideC;
        double angleBCos = (sqr(sideA) + sqr(sideC) - sqr(sideB)) / 2.0 / sideA 
                                                                  / sideC;
        double angleCCos = (sqr(sideB) + sqr(sideA) - sqr(sideC)) / 2.0 / sideB 
                                                                  / sideA;

        if (angleACos > eps && angleBCos > eps && angleCCos > eps) {
            double sinA = sqrt(1 - sqr(angleACos));
            double area = 0.5 * sinA * sideB * sideC;

            cout << endl << "Area: " << area << endl;
        } else if (fuzzyEqual(sideA + sideB, sideC, eps)
                || fuzzyEqual(sideA + sideC, sideB, eps)
                || fuzzyEqual(sideB + sideC, sideA, eps)) 
        {
            // All dots are on the same line
            cout << "Not a triangle" << endl;
        } else {
            cout << "Triangle is not oblique" << endl;
        }
    } else {
        cout << "Not a triangle" << endl;
    }

    return 0;
}
