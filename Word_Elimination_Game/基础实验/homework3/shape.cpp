#include "shape.h"
#include <cmath>
#include <iostream>
using namespace std;

Shape::Shape()
{
    cout << "������һ����״" << endl;
}

Shape::~Shape()
{
    cout << "������һ����״" << endl;
}

Rectangle::Rectangle(double h, double w) : height(h), width(w)
{
    cout << "������һ����Ϊ" << height << "����Ϊ" << width << "�ľ���" << endl;
}

Rectangle::~Rectangle()
{
    cout << "������һ����Ϊ" << height << "����Ϊ" << width << "�ľ���" << endl;
}

double Rectangle::area() const
{
    return width * height;
}

Circle::Circle(double r) : radius(r)
{
    cout << "������һ���뾶Ϊ" << radius << "��Բ��" << endl;
}

Circle::~Circle()
{
    cout << "������һ���뾶Ϊ" << radius << "��Բ��" << endl;
}

double Circle::area() const
{
    return PI * radius * radius;
}

Square::Square(double side) : Rectangle(side, side)
{
    cout << "������һ���߳�Ϊ" << height << "��������" << endl;
}

Square::~Square()
{
    cout << "������һ���߳�Ϊ" << height << "��������" << endl;
}
