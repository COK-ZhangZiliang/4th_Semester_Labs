#include "circle.h"
#include <iostream>
using namespace std;

int main()
{
    double x1 = 0.0, y1 = 0.0, r1;
    double x2 = 0.0, y2 = 0.0, r2;

    cout << "请输入第1个圆的圆心坐标：" << endl;
    if (cin.peek() != '\n')
    {
        cin >> x1 >> y1;
    }
    cout << "请输入第1个圆的半径长度：" << endl;
    cin >> r1;
    while (r1 <= 0)
    {
        cout << "请输入一个值大于0的半径：" << endl;
        cin >> r1;
    }
    Circle c1(r1, x1, y1);
    system("pause");

    getchar();

    cout << "请输入第2个圆的圆心坐标：" << endl;
    if (cin.peek() != '\n')
    {
        cin >> x2 >> y2;
    }
    cout << "请输入第2个圆的半径长度：" << endl;
    cin >> r2;
    while (r2 <= 0)
    {
        cout << "请输入一个值大于0的半径：" << endl;
        cin >> r2;
    }
    Circle c2(r2, x2, y2);
    system("pause");

    if (c1.IsIntersect(c2))
        cout << "两个圆相交" << endl;
    else
        cout << "两个圆不相交" << endl;
    system("pause");

    system("pause");
    return 0;
}
/*

3.3
4 0
0.6
*/