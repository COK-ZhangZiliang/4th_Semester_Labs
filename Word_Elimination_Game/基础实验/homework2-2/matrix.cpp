#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix() : lines(0), rows(0), elem(nullptr)
{
}

Matrix::Matrix(int r, int l) : rows(r), lines(l)
{
    elem = new (nothrow) int *[rows];
    if (elem == nullptr)
    {
        cout << "��̬�����ڴ�ʧ��" << endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        elem[i] = new (nothrow) int[lines];
        if (elem == nullptr)
        {
            cout << "��̬�����ڴ�ʧ��" << endl;
            return;
        }
    }
}

Matrix::Matrix(const Matrix &m) : lines(m.lines), rows(m.rows)
{
    elem = new (nothrow) int *[rows];
    if (elem == nullptr)
    {
        cout << "��̬�����ڴ�ʧ��" << endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        elem[i] = new (nothrow) int[lines];
        if (elem == nullptr)
        {
            cout << "��̬�����ڴ�ʧ��" << endl;
            return;
        }
        for (int j = 0; j < lines; j++)
            elem[i][j] = m.elem[i][j];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        if (elem[i] != nullptr)
        {
            delete[] elem[i];
            elem[i] = nullptr;
        }
    }
    if (elem != nullptr)
    {
        delete[] elem;
        elem = nullptr;
    }
}

void Matrix::input()
{
    cout << "������һ����СΪ" << rows << "��" << lines << "�ľ���" << endl;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < lines; j++)
            cin >> elem[i][j];
}

void Matrix::output()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < lines; j++)
            cout << elem[i][j] << " ";
        cout << endl;
    }
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if (rows != m.rows || lines != m.lines)
    {
        cout << "�������󣺴�С����ͬ�����������޷����ӷ�" << endl;
        exit(1);
    }

    Matrix result(rows, lines);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < lines; j++)
        {
            result.elem[i][j] = elem[i][j] + m.elem[i][j];
        }
    return result;
}

Matrix Matrix::operator-(const Matrix &m) const
{
    if (rows != m.rows || lines != m.lines)
    {
        cout << "�������󣺴�С����ͬ�����������޷�������" << endl;
        exit(1);
    }

    Matrix result(rows, lines);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < lines; j++)
            result.elem[i][j] = elem[i][j] - m.elem[i][j];
    return result;
}

Matrix &Matrix::operator=(const Matrix &m)
{
    if (this != &m)
    {
        this->~Matrix(); // ���ͷſռ�
        rows = m.rows;
        lines = m.lines;
        elem = new (nothrow) int *[rows];
        if (elem == nullptr)
        {
            cout << "��̬�����ڴ�ʧ��" << endl;
            exit(1);
        }
        for (int i = 0; i < rows; i++)
        {
            elem[i] = new (nothrow) int[lines];
            if (elem == nullptr)
            {
                cout << "��̬�����ڴ�ʧ��" << endl;
                exit(1);
            }
            for (int j = 0; j < lines; j++)
                elem[i][j] = m.elem[i][j];
        }
    }
    // �Ը�ֱֵ�ӷ���
    return *this;
}