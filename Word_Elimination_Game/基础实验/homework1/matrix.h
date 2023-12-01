#ifndef MATRIX_H
#define MATRIX_H

const int N = 4;
const int M = 5;

struct matrix
{
    int **elem;
};

// ��ʼ������
void InitMatrix(matrix &m);

// ���뺯��
void InputMatrix(matrix &m);

// �������
void OutputMatrix(const matrix m);

// ��ӵĺ���
// m3 = m1 + m2
void AddMatrix(const matrix m1, const matrix m2, matrix &m3);

// ����ĺ���
// m3 = m1 - m2
void SubMatrix(const matrix m1, const matrix m2, matrix &m3);

// �ͷž���ռ�
void ReleaseMatrix(matrix &m);

#endif
