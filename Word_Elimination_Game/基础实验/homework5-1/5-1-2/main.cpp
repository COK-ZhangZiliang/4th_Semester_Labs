#include "shape.h"
#include <iostream>
using namespace std;

int main()
{
    double h, w;
    double r;
    double s;

    cout << "请输入矩形的长和宽：" << endl;
    cin >> h >> w;
    while (h <= 0 || w <= 0)
    {
        cout << "请输入正数！" << endl;
        cin >> h >> w;
    }
    Rectangle rec(h, w);
    cout << "矩形的面积为：" << rec.area() << endl;
    cout << endl;

    cout << "请输入圆形的半径" << endl;
    cin >> r;
    while (r <= 0)
    {
        cout << "请输入正数！" << endl;
        cin >> r;
    }
    Circle cir(r);
    cout << "圆形的面积为：" << cir.area() << endl;
    cout << endl;

    cout << "请输入正方形的边长" << endl;
    cin >> s;
    while (s <= 0)
    {
        cout << "请输入正数！" << endl;
        cin >> s;
    }
    Square squ(s);
    cout << "正方形的面积为：" << squ.area() << endl;
    cout << endl;

    return 0;
}
