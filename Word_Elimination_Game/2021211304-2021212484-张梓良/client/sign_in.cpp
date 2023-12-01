#include "sign_in.h"
#include "ui_sign_in.h"
#include <QString>
#include <QMessageBox>
#include "user_database.h"
#include <QWidgetAction>
#include <QDebug>

Sign_In::Sign_In(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Sign_In)
{
    ui->setupUi(this);

    this->m_timer = new QTimer(this);
    this->m_timer->start(1000);
    ui->usr_lineEdit->setFocus();
    signup = new Sign_Up(this);
    user_mainwindow = new User_MainWindow(this);
    forget_pass = new forget_password(this);

    //初始显示登录界面
    this->show();
    signup->close();
    forget_pass->close();

    //登录和注册界面切换
    connect(this, &Sign_In::change_to_sign_up, this, [ = ]()
    {
        this->hide();
        signup->clear_info();
        signup->show();
    });
    connect(this->signup, &Sign_Up::change_to_sign_in, this, [ = ]()
    {
        ui->usr_lineEdit->clear();
        ui->pwd_lineEdit->clear();
        ui->usr_lineEdit->setFocus();
        this->show();
        signup->close();
    });

    //在注册界面点击关闭窗口按钮
    connect(this->signup, &Sign_Up::change_to_sign_in, this, [ = ]
    {
        ui->usr_lineEdit->clear();
        ui->pwd_lineEdit->clear();
        ui->usr_lineEdit->setFocus();
        this->show();
    });

    // 点击登录按钮
    connect(ui->signin_btn, &QPushButton::clicked, this, [ = ]()
    {
        //获取输入的用户名和密码
        QString username = ui->usr_lineEdit->text();
        QString password = ui->pwd_lineEdit->text();

        if(username != "" && password != "")
        {
            //创建数据库对象
            //获取用户数据库的连接
            User_Database userdb;

            //用户存在
            if(userdb.findUser(username))
            {
                //密码正确
                int check = userdb.checkPassword(username, password);
                if( check == 1)
                {
                    int role, level, experience, questionCount, passedLevels;
                    userdb.getUser(username, role, level, experience, questionCount, passedLevels);
                    user_mainwindow->setPushbutton(role);
                    user_mainwindow->statusbar_info(username, role, level, experience, questionCount, passedLevels);
                    QMessageBox::information(this, "提示", "登录成功!");

                    //获取用户信息
                    connect(m_timer, &QTimer::timeout, this, [ = ]()
                    {
                        int role, level, experience, questionCount, passedLevels;
                        userdb.getUser(username, role, level, experience, questionCount, passedLevels);
                        //qDebug() << role << level << experience << questionCount << passedLevels;
                        //状态栏显示用户信息
                        user_mainwindow->statusbar_info(username, role, level, experience, questionCount, passedLevels);
                    });
                    //启动游戏
                    connect(user_mainwindow, &User_MainWindow::update_info, this, [ = ](int addExp, int new_passedLevels, int new_questionCount)
                    {
                        int role, level, experience, questionCount, passedLevels;
                        userdb.getUser(username, role, level, experience, questionCount, passedLevels);
                        if(experience + addExp >= 100)
                        {
                            level++;
                        }
                        experience = (experience + addExp) % 100;
                        if(new_passedLevels > passedLevels)
                        {
                            passedLevels = new_passedLevels;
                        }
                        questionCount += new_questionCount;
                        userdb.updateUser(username, level, experience, questionCount, passedLevels);
                    });
                    this->hide();
                    user_mainwindow->show();
                }
                //密码错误
                else if (check == -1)
                {
                    QMessageBox::critical(this, "错误", "密码错误！");
                }
                // 用户已登录
                else
                {
                    QMessageBox::critical(this, "错误", "用户已登录！");
                }
            }
            //用户不存在
            else
            {
                QMessageBox::critical(this, "错误", "用户不存在！");
            }
        }
        //对输入为空的情况的判定
        else
        {
            if(username == "" && password == "")
            {
                QMessageBox::information(this, "提示", "请输入用户名和密码!");
            }
            else if(username == "")
            {
                QMessageBox::information(this, "提示", "请输入用户名!");

            }
            else
            {
                QMessageBox::information(this, "提示", "请输入密码!");
            }
        }
    });

    // 点击注册按钮
    connect(ui->signup_btn, &QPushButton::clicked, this, [ = ]()
    {
        // QMessageBox::information(this, "提示", "注册!");
        emit change_to_sign_up();
    });

    // 显示密码
    ui->show_pwd->setIcon(QIcon(":/sign_in/hide_pwd.png"));
    ui->show_pwd->setCheckable(true);
    ui->show_pwd->setStyleSheet("border:none;");                 // 去掉按钮边框
    QWidgetAction* action = new QWidgetAction(ui->pwd_lineEdit); // 在密码编辑框的右侧加上显示密码按钮
    action->setDefaultWidget(ui->show_pwd);
    ui->pwd_lineEdit->addAction(action, QLineEdit::TrailingPosition);
    // 按下显示密码按钮
    connect(ui->show_pwd, &QPushButton::toggled, this, [ = ](bool checked)
    {
        //显示密码
        if(checked)
        {
            ui->pwd_lineEdit->setEchoMode(QLineEdit::Normal);
            ui->show_pwd->setIcon(QIcon(":/sign_in/show_pwd.png"));
            qDebug() << "显示密码";
        }
        //隐藏密码
        else
        {
            ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
            ui->show_pwd->setIcon(QIcon(":/sign_in/hide_pwd.png"));
            qDebug() << "隐藏密码";
        }
    });

    //在用户主页面点击关闭按钮,关闭所有窗口
    connect(user_mainwindow, &User_MainWindow::close_all, this, [ = ]()
    {
        qApp->quit();
    });

    //点击忘记密码按钮
    connect(this, &Sign_In::forget, forget_pass, [ = ]()
    {
        this->hide();
        forget_pass->show();
    });
    connect(forget_pass, &forget_password::change_to_sign_in, this, [ = ]()
    {
        forget_pass->hide();
        this->show();
    });
}

Sign_In::~Sign_In()
{
    delete ui;
}

void Sign_In::on_pushButton_clicked()
{
    emit forget();
}


void Sign_In::on_help_btn_clicked()
{
    QMessageBox::information(this, "帮助", "这是一款单词消除小游戏\n你可以选择成为出题者或者挑战者\n出题者可以为游戏题库增加题目\n挑战者可以进行单词消除挑战\n邮件联系ziliangzhang.bupt.edu.cn获取更多详情");
}

