#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    // ���캯��
    Matrix();
    Matrix(int r, int l);
    Matrix(const Matrix &m);
    // ��������
    ~Matrix();

    void input();
    void output();

    // �������������=��+��-��������
    // ע�⣺���ڲ��������ز�������-1
    Matrix &operator=(const Matrix &m);
    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    int rows, lines; // �С���
    int **elem;      // ����Ԫ��
};

#endif