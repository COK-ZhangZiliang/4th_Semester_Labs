#include "matrix.h"
#include <iostream>
#include <new>
using namespace std;

// 初始化函数
void InitMatrix(matrix &m)
{
    m.elem = new (nothrow) int *[4];
    if (m.elem == nullptr)
    {
        cout << "初始化失败" << endl;
        return;
    }
    for (int i = 0; i < N; i++)
    {
        m.elem[i] = new (nothrow) int[M];
        if (m.elem[i] == nullptr)
        {
            cout << "初始化失败" << endl;
            return;
        }
    }
}

// 输入函数
void InputMatrix(matrix &m)
{
    cout << "请输入一个大小为4×5的矩阵:" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> m.elem[i][j];
}

// 输出函数
void OutputMatrix(const matrix m)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << m.elem[i][j] << " ";
        cout << endl;
    }
}

// 相加的函数
// m3 = m1 + m2
void AddMatrix(const matrix m1, const matrix m2, matrix &m3)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            m3.elem[i][j] = m1.elem[i][j] + m2.elem[i][j];
}

// 相减的函数
// m3 = m1 - m2
void SubMatrix(const matrix m1, const matrix m2, matrix &m3)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            m3.elem[i][j] = m1.elem[i][j] - m2.elem[i][j];
}

// 释放矩阵空间
void ReleaseMatrix(matrix &m)
{
    for (int i = 0; i < N; i++)
    {
        if (m.elem[i] != nullptr)
        {
            delete[] m.elem[i];
            m.elem[i] = nullptr;
        }
    }
    if (m.elem != nullptr)
    {
        delete[] m.elem;
        m.elem = nullptr;
    }
}