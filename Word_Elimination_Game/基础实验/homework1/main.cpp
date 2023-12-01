#include "matrix.h"
#include <iostream>
using namespace std;

int main()
{
    matrix A1, A2, A3;

    InitMatrix(A1);
    InitMatrix(A2);
    InitMatrix(A3);

    InputMatrix(A1);
    InputMatrix(A2);

    AddMatrix(A1, A2, A3);
    cout << "A1加A2的结果为：" << endl;
    OutputMatrix(A3);

    SubMatrix(A1, A2, A3);
    cout << "A1减A2的结果为：" << endl;
    OutputMatrix(A3);

    ReleaseMatrix(A1);
    ReleaseMatrix(A2);
    ReleaseMatrix(A3);

    return 0;
}
/*
1 1 1 1 1
2 2 2 2 2
3 3 3 3 3
4 4 4 4 4
4 4 4 4 4
3 3 3 3 3
2 2 2 2 2
1 1 1 1 1
*/