#ifndef FORGET_PASSWORD_H
#define FORGET_PASSWORD_H

#include <QMainWindow>

namespace Ui
{
    class forget_password;
}

class forget_password : public QMainWindow
{
    Q_OBJECT

public:
    explicit forget_password(QWidget* parent = nullptr);
    ~forget_password();

    void closeEvent(QCloseEvent* event);

private slots:
    void on_confirm_pushButton_clicked();

    void on_search_pushButton_clicked();

signals:
    // 切换到登录窗口的信号
    void change_to_sign_in();

private:
    Ui::forget_password* ui;
};

#endif // FORGET_PASSWORD_H
