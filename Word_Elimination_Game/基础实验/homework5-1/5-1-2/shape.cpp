#include "shape.h"
#include <cmath>
#include <iostream>
using namespace std;

Shape::Shape()
{
    cout << "构造了一个形状" << endl;
}

Shape::~Shape()
{
    cout << "析构了一个形状" << endl;
}

Rectangle::Rectangle(double h, double w) : height(h), width(w)
{
    cout << "构造了一个长为" << height << "，宽为" << width << "的矩形" << endl;
}

Rectangle::~Rectangle()
{
    cout << "析构了一个长为" << height << "，宽为" << width << "的矩形" << endl;
}

double Rectangle::area() const
{
    return width * height;
}

Circle::Circle(double r) : radius(r)
{
    cout << "构造了一个半径为" << radius << "的圆形" << endl;
}

Circle::~Circle()
{
    cout << "析构了一个半径为" << radius << "的圆形" << endl;
}

double Circle::area() const
{
    return PI * radius * radius;
}

Square::Square(double side) : Rectangle(side, side)
{
    cout << "构造了一个边长为" << height << "的正方形" << endl;
}

Square::~Square()
{
    cout << "析构了一个边长为" << height << "的正方形" << endl;
}
