#include "shape.h"
#include <iostream>
using namespace std;

int main()
{
    double h, w;
    double r;
    double s;

    cout << "��������εĳ��Ϳ�" << endl;
    cin >> h >> w;
    while (h <= 0 || w <= 0)
    {
        cout << "������������" << endl;
        cin >> h >> w;
    }
    Rectangle rec(h, w);
    cout << "���ε����Ϊ��" << rec.area() << endl;
    cout << endl;

    cout << "������Բ�εİ뾶" << endl;
    cin >> r;
    while (r <= 0)
    {
        cout << "������������" << endl;
        cin >> r;
    }
    Circle cir(r);
    cout << "Բ�ε����Ϊ��" << cir.area() << endl;
    cout << endl;

    cout << "�����������εı߳�" << endl;
    cin >> s;
    while (s <= 0)
    {
        cout << "������������" << endl;
        cin >> s;
    }
    Square squ(s);
    cout << "�����ε����Ϊ��" << squ.area() << endl;
    cout << endl;

    return 0;
}
