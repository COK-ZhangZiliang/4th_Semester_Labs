#include "forget_password.h"
#include "ui_forget_password.h"
#include "user_database.h"
#include <QMessageBox>

forget_password::forget_password(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::forget_password)
{
    ui->setupUi(this);
    ui->usr_lineEdit->clear();
    ui->new_pass_lineEdit->clear();
    ui->confirm_lineEdit->clear();
    ui->que_label->clear();
    ui->ans_lineEdit->clear();
}

forget_password::~forget_password()
{
    delete ui;
}

void forget_password::on_search_pushButton_clicked()
{
    User_Database user_db;
    QString username = ui->usr_lineEdit->text();
    if(user_db.findUser(ui->usr_lineEdit->text()))
    {
        ui->que_label->setText(user_db.getQue(username));
    }
    else
    {
        QMessageBox::critical(this, "错误", "用户不存在！");
    }
}


void forget_password::on_confirm_pushButton_clicked()
{
    User_Database user_db;
    QString ans = ui->ans_lineEdit->text();
    QString username = ui->usr_lineEdit->text();
    if(user_db.checkAns(username, ans))
    {
        QString password = ui->new_pass_lineEdit->text();
        QString confirm_password = ui->confirm_lineEdit->text();
        if(password == confirm_password)
        {
            user_db.resetPassword(username, password);
            QMessageBox::information(this, "提示", "重置密码成功");
            emit change_to_sign_in();
        }
        else
        {
            QMessageBox::critical(this, "错误", "两次输入的密码不一致！");
        }
    }
    else
    {
        QMessageBox::critical(this, "错误", "答案错误！");
    }
}

void forget_password::closeEvent(QCloseEvent* event)
{
    // 切换到登录窗口
    emit change_to_sign_in();
}


