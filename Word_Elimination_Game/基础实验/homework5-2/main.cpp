#include "point.h"

int main()
{
    double x, y;

    cout << "�����������꣺" << endl;
    cin >> x >> y;
    Point p(x, y);

    cout << "++p=" << ++p << " "
         << "++p֮��p=" << p << endl;
    cout << "--p=" << --p << " "
         << "--p֮��p=" << p << endl;
    cout << "p++=" << p++ << " "
         << "p++֮��p=" << p << endl;
    cout << "p--=" << p-- << " "
         << "p--֮��p=" << p << endl;

    return 0;
}