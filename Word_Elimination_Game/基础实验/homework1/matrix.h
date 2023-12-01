#ifndef MATRIX_H
#define MATRIX_H

const int N = 4;
const int M = 5;

struct matrix
{
    int **elem;
};

// 初始化函数
void InitMatrix(matrix &m);

// 输入函数
void InputMatrix(matrix &m);

// 输出函数
void OutputMatrix(const matrix m);

// 相加的函数
// m3 = m1 + m2
void AddMatrix(const matrix m1, const matrix m2, matrix &m3);

// 相减的函数
// m3 = m1 - m2
void SubMatrix(const matrix m1, const matrix m2, matrix &m3);

// 释放矩阵空间
void ReleaseMatrix(matrix &m);

#endif
