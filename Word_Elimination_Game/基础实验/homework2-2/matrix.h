#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    // 构造函数
    Matrix();
    Matrix(int r, int l);
    Matrix(const Matrix &m);
    // 析构函数
    ~Matrix();

    void input();
    void output();

    // 对运算操作符“=、+、-”的重载
    // 注意：类内操作符重载参数个数-1
    Matrix &operator=(const Matrix &m);
    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    int rows, lines; // 行、列
    int **elem;      // 矩阵元素
};

#endif