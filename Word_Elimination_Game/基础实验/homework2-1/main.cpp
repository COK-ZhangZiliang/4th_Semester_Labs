#include "circle.h"
#include <iostream>
using namespace std;

int main()
{
    double x1 = 0.0, y1 = 0.0, r1;
    double x2 = 0.0, y2 = 0.0, r2;

    cout << "�������1��Բ��Բ�����꣺" << endl;
    if (cin.peek() != '\n')
    {
        cin >> x1 >> y1;
    }
    cout << "�������1��Բ�İ뾶���ȣ�" << endl;
    cin >> r1;
    while (r1 <= 0)
    {
        cout << "������һ��ֵ����0�İ뾶��" << endl;
        cin >> r1;
    }
    Circle c1(r1, x1, y1);
    system("pause");

    getchar();

    cout << "�������2��Բ��Բ�����꣺" << endl;
    if (cin.peek() != '\n')
    {
        cin >> x2 >> y2;
    }
    cout << "�������2��Բ�İ뾶���ȣ�" << endl;
    cin >> r2;
    while (r2 <= 0)
    {
        cout << "������һ��ֵ����0�İ뾶��" << endl;
        cin >> r2;
    }
    Circle c2(r2, x2, y2);
    system("pause");

    if (c1.IsIntersect(c2))
        cout << "����Բ�ཻ" << endl;
    else
        cout << "����Բ���ཻ" << endl;
    system("pause");

    system("pause");
    return 0;
}
/*

3.3
4 0
0.6
*/