#include "circle.h"
#include <iostream>
#include <cmath>
using namespace std;

Point::Point(double x1, double y1) : x(x1), y(y1)
{
    cout << "创建了一个坐标为 (" << x << ", " << y << ") 的点" << endl;
}

Point::~Point()
{
    cout << "销毁了一个坐标为 (" << x << ", " << y << ") 的点" << endl;
}

// 计算两点之间的距离
double Point::CalDis(const Point &point) const
{
    return sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
}

Circle::Circle(double r1, double x1, double y1) : r(r1), center(x1, y1)
{
    cout << "创建了一个圆心为 (" << center.x << ", " << center.y
         << ") ,半径为 " << r << " 的圆" << endl;
}

Circle::~Circle()
{
    cout << "销毁了一个圆心为 (" << center.x << ", " << center.y
         << ") ,半径为 " << r << " 的圆" << endl;
}

// 判断两个圆是否相交
bool Circle::IsIntersect(const Circle c) const
{
    double delta = center.CalDis(c.center) - r - c.r;
    if (delta > 1e-6)
        return false;
    else
        return true;
}
