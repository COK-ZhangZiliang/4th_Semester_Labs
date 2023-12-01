#include "sign_up.h"
#include "ui_sign_up.h"
#include <QString>
#include <QMessageBox>
#include "user_database.h"
#include <QWidgetAction>
#include <QDebug>
#include "user.h"

Sign_Up::Sign_Up(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::Sign_Up)
{
    ui->setupUi(this);
    ui->usr_lineEdit->setFocus();

    // 点击注册按钮
    connect(ui->signup_btn, &QPushButton::clicked, this, [ = ]()
    {
        //获取输入的用户名、密码、和确认密码以及选择的角色
        QString username = ui->usr_lineEdit->text();
        QString password = ui->pwd_lineEdit->text();
        QString confirm_password = ui->confirm_pwd_lineEdit->text();
        QString question = ui->question_lineEdit->text();
        QString answer = ui->answer_lineEdit->text();
        int role = ui->role_comboBox->currentIndex();

        if(username != "" && password != "" && confirm_password != "" && question != "" && answer != "")
        {
            //创建数据库对象
            //获取用户数据库的连接
            User_Database userdb;

            //用户存在
            if(userdb.findUser(username))
            {
                QMessageBox::critical(this, "错误", "用户名已存在！");
            }
            //用户不存在
            else
            {
                // 判断两次输入的密码是否一致
                if(password == confirm_password)
                {
                    //确认注册信息是否正确

                    //创建新的用户并添加进用户数据库
                    User new_user(username, password, 0);
                    userdb.addUser(new_user, role, question, answer);
                    QMessageBox::information(this, "提示", "注册成功!");
                    //返回登录界面
                    emit change_to_sign_in();
                }
                else
                {
                    QMessageBox::critical(this, "错误", "两次输入的密码不一致！");
                }
            }
        }
        //输入信息不全
        else
        {
            QMessageBox::information(this, "提示", "请填写所有注册信息!");
        }
    });

    // 点击返回按钮
    connect(ui->back_to_signin_btn, &QPushButton::clicked, this, [ = ]()
    {
        //返回登录界面
        emit change_to_sign_in();
    });

    // 显示密码
    ui->show_pwd_1->setIcon(QIcon(":/sign_in/hide_pwd.png"));
    ui->show_pwd_1->setCheckable(true);
    ui->show_pwd_1->setStyleSheet("border:none;");                // 去掉按钮边框
    QWidgetAction* action1 = new QWidgetAction(ui->pwd_lineEdit); // 在密码编辑框的右侧加上显示密码按钮
    action1->setDefaultWidget(ui->show_pwd_1);
    ui->pwd_lineEdit->addAction(action1, QLineEdit::TrailingPosition);
    // 按下显示密码按钮
    connect(ui->show_pwd_1, &QPushButton::toggled, this, [ = ](bool checked)
    {
        //显示密码
        if(checked)
        {
            ui->pwd_lineEdit->setEchoMode(QLineEdit::Normal);
            ui->show_pwd_1->setIcon(QIcon(":/sign_in/show_pwd.png"));
            qDebug() << "显示密码";
        }
        //隐藏密码
        else
        {
            ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
            ui->show_pwd_1->setIcon(QIcon(":/sign_in/hide_pwd.png"));
            qDebug() << "隐藏密码";
        }
    });
    ui->show_pwd_2->setIcon(QIcon(":/sign_in/hide_pwd.png"));
    ui->show_pwd_2->setCheckable(true);
    ui->show_pwd_2->setStyleSheet("border:none;");                        // 去掉按钮边框
    QWidgetAction* action2 = new QWidgetAction(ui->confirm_pwd_lineEdit); // 在密码编辑框的右侧加上显示密码按钮
    action2->setDefaultWidget(ui->show_pwd_2);
    ui->confirm_pwd_lineEdit->addAction(action2, QLineEdit::TrailingPosition);
    // 按下显示密码按钮
    connect(ui->show_pwd_2, &QPushButton::toggled, this, [ = ](bool checked)
    {
        //显示密码
        if(checked)
        {
            ui->confirm_pwd_lineEdit->setEchoMode(QLineEdit::Normal);
            ui->show_pwd_2->setIcon(QIcon(":/sign_in/show_pwd.png"));
            qDebug() << "显示密码";
        }
        //隐藏密码
        else
        {
            ui->confirm_pwd_lineEdit->setEchoMode(QLineEdit::Password);
            ui->show_pwd_2->setIcon(QIcon(":/sign_in/hide_pwd.png"));
            qDebug() << "隐藏密码";
        }
    });
}

Sign_Up::~Sign_Up()
{
    delete ui;
}

void Sign_Up::clear_info()
{
    ui->usr_lineEdit->setFocus();
    ui->usr_lineEdit->clear();
    ui->pwd_lineEdit->clear();
    ui->confirm_pwd_lineEdit->clear();
    ui->question_lineEdit->clear();
    ui->answer_lineEdit->clear();
    ui->role_comboBox->setCurrentIndex(0);
}

void Sign_Up::closeEvent(QCloseEvent* event)
{
    // 切换到登录窗口
    emit change_to_sign_in();
}

void Sign_Up::on_help_btn_clicked()
{
    QMessageBox::information(this, "帮助", "这是一款单词消除小游戏\n你可以选择成为出题者或者挑战者\n出题者可以为游戏题库增加题目\n挑战者可以进行单词消除挑战\n邮件联系ziliangzhang.bupt.edu.cn获取更多详情");
}

