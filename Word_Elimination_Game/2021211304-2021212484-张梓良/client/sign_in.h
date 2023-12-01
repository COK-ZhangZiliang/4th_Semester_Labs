#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMainWindow>
#include "sign_up.h"
#include "user_mainwindow.h"
#include "forget_password.h"

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
    // 忘记密码
    void forget();

private:
    Ui::Sign_In* ui;
    Sign_Up* signup;
    forget_password* forget_pass;

public:
    User_MainWindow* user_mainwindow;
    QTimer* m_timer;
private slots:
    void on_pushButton_clicked();
    void on_help_btn_clicked();
};

#endif // SIGN_IN_H
