#include <iostream>
#include <ctime>
#include <random>
using namespace std;

int main()
{
    double guess = 0, price;

    // �������һ��1-1000������
    default_random_engine e;
    uniform_int_distribution<int> u(1, 1000);
    e.seed(time(0));
    price = u(e);
    // cout << price << endl;

    cout << "***** ����һ���¼۸����Ϸ ***** " << endl;
    cout << "** ��Ʒ�ļ۸�ķ�ΧΪ1-1000Ԫ ** " << endl;

    while (guess != price)
    {
        cout << "��������µļ۸�1-1000����������" << endl;
        cin >> guess;

        // ���������
        if (cin.fail())
        {
            cin.clear();            // ���cin�Ĵ���״̬
            cin.ignore(1024, '\n'); // ���Ի����������ݣ�ֱ��EOF
            cout << "�Ƿ����룺������������" << endl;
        }
        // ����С��
        else if (guess - int(guess))
            cout << "�Ƿ����룺������������" << endl;
        // ������Χ
        else if (guess < 1 || guess > 1000)
            cout << "�Ƿ����룺������ΧӦ��1-1000��" << endl;

        else if (guess > price)
            cout
                << "����ֵ���ڼ۸�" << endl;
        else if (guess < price)
            cout
                << "����ֵ���ڼ۸�" << endl;
        else
            cout << "�¶�����" << endl;
    }

    return 0;
}