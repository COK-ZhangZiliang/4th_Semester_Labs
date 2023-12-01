#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMainWindow>
#include "sign_up.h"
#include "user_mainwindow.h"

namespace Ui
{
    class Sign_In;
}

class Sign_In : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sign_In(QWidget* parent = nullptr);
    ~Sign_In();

signals:
    // 切换到注册窗口的信号
    void change_to_sign_up();

private:
    Ui::Sign_In* ui;
    Sign_Up* signup;
public:
    User_MainWindow* user_mainwindow;
};

#endif // SIGN_IN_H
