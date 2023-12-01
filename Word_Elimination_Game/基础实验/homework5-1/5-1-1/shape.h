#ifndef SHAPE_H
#define SHAPE_H

const double PI = 3.14159265358979323846;

// ��״��
class Shape
{
public:
    Shape();
    ~Shape();
    // �麯��
    // �������
    virtual double area();
};

// Shape���������������
class Rectangle : public Shape
{
protected:
    double height, width;

public:
    Rectangle(double h, double w);
    ~Rectangle();
    virtual double area() const;
};

// Shape���������Բ����
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r);
    ~Circle();
    virtual double area() const;
};

// ���������������������
class Square : public Rectangle
{
public:
    Square(double side);
    ~Square();
};

#endif