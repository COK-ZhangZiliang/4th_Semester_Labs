#ifndef SHAPE_H
#define SHAPE_H

const double PI = 3.14159265358979323846;

// 形状类
// 抽象类
class Shape
{
public:
    Shape();
    ~Shape();
    // 纯虚函数
    // 计算面积
    virtual double area() const = 0;
};

// Shape类的派生：矩形类
class Rectangle : public Shape
{
protected:
    double height, width;

public:
    Rectangle(double h, double w);
    ~Rectangle();
    double area() const;
};

// Shape类的派生：圆形类
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r);
    ~Circle();
    double area() const;
};

// 矩形类的派生：正方形类
class Square : public Rectangle
{
public:
    Square(double side);
    ~Square();
};

#endif