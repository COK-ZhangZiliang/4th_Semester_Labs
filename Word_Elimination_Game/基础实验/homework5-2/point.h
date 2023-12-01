#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;

class Point
{
    friend ostream &operator<<(ostream &cout, const Point &p);

public:
    Point(double x1, double y1);
    ~Point();
    Point(Point &p);

    Point &operator++();
    Point &operator--();
    Point operator++(int);
    Point operator--(int);

private:
    double x, y; // µãµÄ×ø±ê
};

#endif