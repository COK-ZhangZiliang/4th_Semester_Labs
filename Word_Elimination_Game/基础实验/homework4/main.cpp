#include <iostream>
#include <ctime>
#include <random>
using namespace std;

int main()
{
    double guess = 0, price;

    // 随机产生一个1-1000的整数
    default_random_engine e;
    uniform_int_distribution<int> u(1, 1000);
    e.seed(time(0));
    price = u(e);
    // cout << price << endl;

    cout << "***** 这是一个猜价格的游戏 ***** " << endl;
    cout << "** 商品的价格的范围为1-1000元 ** " << endl;

    while (guess != price)
    {
        cout << "请输入你猜的价格（1-1000的整数）：" << endl;
        cin >> guess;

        // 输入非数字
        if (cin.fail())
        {
            cin.clear();            // 清除cin的错误状态
            cin.ignore(1024, '\n'); // 忽略缓冲区的内容，直到EOF
            cout << "非法输入：请输入整数！" << endl;
        }
        // 输入小数
        else if (guess - int(guess))
            cout << "非法输入：请输入整数！" << endl;
        // 超出范围
        else if (guess < 1 || guess > 1000)
            cout << "非法输入：整数范围应是1-1000！" << endl;

        else if (guess > price)
            cout
                << "输入值高于价格" << endl;
        else if (guess < price)
            cout
                << "输入值低于价格" << endl;
        else
            cout << "猜对啦！" << endl;
    }

    return 0;
}