#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sign_in.h"
#include "sign_up.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Sign_In* signin = new Sign_In(this);
    Sign_Up* signup = new Sign_Up(this);

    //初始显示登录界面
    signin->show();
    signup->close();

    //连接信号和槽函数
    connect(signin, &Sign_In::change_to_sign_up, this, [ = ]()
    {
        signin->close();
        signup->show();
    });
    connect(signup, &Sign_Up::change_to_sign_in, this, [ = ]()
    {
        signin->show();
        signup->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
