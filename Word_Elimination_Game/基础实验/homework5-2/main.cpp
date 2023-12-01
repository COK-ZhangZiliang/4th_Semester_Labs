#include "point.h"

int main()
{
    double x, y;

    cout << "请输入点的坐标：" << endl;
    cin >> x >> y;
    Point p(x, y);

    cout << "++p=" << ++p << " "
         << "++p之后p=" << p << endl;
    cout << "--p=" << --p << " "
         << "--p之后p=" << p << endl;
    cout << "p++=" << p++ << " "
         << "p++之后p=" << p << endl;
    cout << "p--=" << p-- << " "
         << "p--之后p=" << p << endl;

    return 0;
}