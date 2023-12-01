#include "point.h"

Point::Point(double x1, double y1) : x(x1), y(y1)
{
    // cout << "构造了一个坐标为 (" << x << ", " << y << ") 的点" << endl;
}

Point::~Point()
{
    // cout << "析构了一个坐标为 (" << x << ", " << y << ") 的点" << endl;
}

Point::Point(Point &p)
{
    x = p.x;
    y = p.y;
    // cout << "拷贝构造了一个坐标为 (" << x << ", " << y << ") 的点" << endl;
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