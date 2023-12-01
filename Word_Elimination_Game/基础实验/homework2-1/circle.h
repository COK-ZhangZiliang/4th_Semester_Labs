#ifndef CIRCLE_H
#define CIRCLE_H

class Point
{
public:
    Point(double x1, double y1);
    ~Point();

    // ��������֮��ľ���
    double CalDis(const Point &point) const;

    double x, y; // �������
};

class Circle
{
public:
    Circle(double r1, double x1 = 0.0, double y1 = 0.0);
    ~Circle();

    // �ж�����Բ�Ƿ��ཻ
    bool IsIntersect(const Circle c) const;

private:
    double r;     // �뾶
    Point center; // Բ��
};

#endif