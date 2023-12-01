#include "circle.h"
#include <iostream>
#include <cmath>
using namespace std;

Point::Point(double x1, double y1) : x(x1), y(y1)
{
    cout << "������һ������Ϊ (" << x << ", " << y << ") �ĵ�" << endl;
}

Point::~Point()
{
    cout << "������һ������Ϊ (" << x << ", " << y << ") �ĵ�" << endl;
}

// ��������֮��ľ���
double Point::CalDis(const Point &point) const
{
    return sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
}

Circle::Circle(double r1, double x1, double y1) : r(r1), center(x1, y1)
{
    cout << "������һ��Բ��Ϊ (" << center.x << ", " << center.y
         << ") ,�뾶Ϊ " << r << " ��Բ" << endl;
}

Circle::~Circle()
{
    cout << "������һ��Բ��Ϊ (" << center.x << ", " << center.y
         << ") ,�뾶Ϊ " << r << " ��Բ" << endl;
}

// �ж�����Բ�Ƿ��ཻ
bool Circle::IsIntersect(const Circle c) const
{
    double delta = center.CalDis(c.center) - r - c.r;
    if (delta > 1e-6)
        return false;
    else
        return true;
}
