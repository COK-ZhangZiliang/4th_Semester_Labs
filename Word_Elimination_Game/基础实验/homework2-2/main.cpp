#include "matrix.h"
#include <iostream>
using namespace std;

int main()
{
    int r1, l1;
    int r2, l2;

    cout << "请输入矩阵A1的大小：" << endl;
    cin >> r1 >> l1;
    Matrix A1(r1, l1);
    A1.input();

    cout << "请输入矩阵A2的大小：" << endl;
    cin >> r2 >> l2;
    Matrix A2(r2, l2);
    A2.input();

    Matrix A3 = A1 + A2;
    cout << "A3=A1+A2的计算结果为：" << endl;
    A3.output();
    A3 = A1 - A2;
    cout << "A3=A1-A2的计算结果为：" << endl;
    A3.output();

    cout << "请输入矩阵pA1的大小：" << endl;
    cin >> r1 >> l1;
    Matrix *pA1 = new Matrix(r1, l1);
    pA1->input();

    cout << "请输入矩阵pA2的大小：" << endl;
    cin >> r2 >> l2;
    Matrix *pA2 = new Matrix(r2, l2);
    pA2->input();

    Matrix *pA3 = new Matrix;
    *pA3 = *pA1 + *pA2;
    cout << "pA3=pA1+pA2的计算结果为：" << endl;
    pA3->output();
    *pA3 = *pA1 - *pA2;
    cout << "pA3=pA1-pA2的计算结果为：" << endl;
    pA3->output();

    // 释放 pA1、pA2、pA3
    delete pA1;
    delete pA2;
    delete pA3;

    return 0;
}
/*
3 4
1 1 1 1
2 2 2 2
3 3 3 3
3 4
1 1 1 1
2 2 2 2
3 3 3 3
3 4
1 1 1 1
2 2 2 2
3 3 3 3
3 4
1 1 1 1
2 2 2 2
3 3 3 3
*/