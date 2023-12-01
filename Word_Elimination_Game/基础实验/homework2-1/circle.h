#ifndef CIRCLE_H
#define CIRCLE_H

class Point
{
public:
    Point(double x1, double y1);
    ~Point();

    // 计算两点之间的距离
    double CalDis(const Point &point) const;

    double x, y; // 点的坐标
};

class Circle
{
public:
    Circle(double r1, double x1 = 0.0, double y1 = 0.0);
    ~Circle();

    // 判断两个圆是否相交
    bool IsIntersect(const Circle c) const;

private:
    double r;     // 半径
    Point center; // 圆心
};

#endif