#include "matrix.h"
#include <iostream>
#include <new>
using namespace std;

// ��ʼ������
void InitMatrix(matrix &m)
{
    m.elem = new (nothrow) int *[4];
    if (m.elem == nullptr)
    {
        cout << "��ʼ��ʧ��" << endl;
        return;
    }
    for (int i = 0; i < N; i++)
    {
        m.elem[i] = new (nothrow) int[M];
        if (m.elem[i] == nullptr)
        {
            cout << "��ʼ��ʧ��" << endl;
            return;
        }
    }
}

// ���뺯��
void InputMatrix(matrix &m)
{
    cout << "������һ����СΪ4��5�ľ���:" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> m.elem[i][j];
}

// �������
void OutputMatrix(const matrix m)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << m.elem[i][j] << " ";
        cout << endl;
    }
}

// ��ӵĺ���
// m3 = m1 + m2
void AddMatrix(const matrix m1, const matrix m2, matrix &m3)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            m3.elem[i][j] = m1.elem[i][j] + m2.elem[i][j];
}

// ����ĺ���
// m3 = m1 - m2
void SubMatrix(const matrix m1, const matrix m2, matrix &m3)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            m3.elem[i][j] = m1.elem[i][j] - m2.elem[i][j];
}

// �ͷž���ռ�
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