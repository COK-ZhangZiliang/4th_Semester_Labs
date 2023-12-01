#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui
{
    class Sign_Up;
}

class Sign_Up : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sign_Up(QWidget* parent = nullptr);
    ~Sign_Up();
    // 清除信息
    void clear_info();
    // 覆写closeEvent函数
    void closeEvent(QCloseEvent* event);

signals:
    // 切换到登录窗口的信号
    void change_to_sign_in();

private:
    Ui::Sign_Up* ui;
};

#endif // SIGN_UP_H
