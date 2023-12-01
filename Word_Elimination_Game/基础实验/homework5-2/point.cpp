#include "point.h"

Point::Point(double x1, double y1) : x(x1), y(y1)
{
    // cout << "������һ������Ϊ (" << x << ", " << y << ") �ĵ�" << endl;
}

Point::~Point()
{
    // cout << "������һ������Ϊ (" << x << ", " << y << ") �ĵ�" << endl;
}

Point::Point(Point &p)
{
    x = p.x;
    y = p.y;
    // cout << "����������һ������Ϊ (" << x << ", " << y << ") �ĵ�" << endl;
}

Point &Point::operator++()
{
    x++, y++;
    return *this;
}

Point &Point::operator--()
{
    x--, y--;
    return *this;
}

Point Point::operator++(int)
{
    Point temp = *this;
    x++, y++;
    return temp;
}

Point Point::operator--(int)
{
    Point temp = *this;
    x--, y--;
    return temp;
}

ostream &operator<<(ostream &cout, const Point &p)
{
    cout << "(" << p.x << "," << p.y << ")";
    return cout;
}