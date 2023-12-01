#include "pvp.h"
#include "ui_pvp.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>

Pvp::Pvp(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Pvp)
{
    ui->setupUi(this);
    this->m_timer = new QTimer(this);

    // 使用正则表达式限制输入只能为大小写英文字母
    QRegularExpression regExp("[A-Za-z]+");
    QValidator* validator = new QRegularExpressionValidator(regExp, this);
    ui->pvp_input_word_lineEdit->setValidator(validator);

    connect(m_timer, &QTimer::timeout, this, [ = ]
    {
        ui->rest_time_progressBar->setValue(--rest_time);

        // 判断是否还剩余时间
        if(!rest_time)
        {
            m_timer->stop();
            // 单词消失
            ui->pvp_show_word_label->hide();
            // 允许用户输入
            ui->pvp_input_word_lineEdit->setEnabled(true);
            ui->pvp_input_word_lineEdit->setFocus();
            cost_time++;
        }
    });
}

Pvp::~Pvp()
{
    delete ui;
}

void Pvp::showInfo()
{
    ui->pvp_input_word_lineEdit->setEnabled(false);
    this->rest_time = 5;
    ui->rest_time_progressBar->setMaximum(this->rest_time);

    // 显示当前轮数和对手信息
    ui->current_round_label->setText(QString("当前轮数：%1/10").arg(this->current_round));
    ui->opponent_label->setText(QString("挑战者：%1").arg(this->opponent));
    ui->statusbar->addWidget(ui->current_round_label);
    ui->statusbar->addWidget(ui->opponent_label);

    // 显示单词
    ui->pvp_show_word_label->setText(words[current_round - 1]);
    ui->pvp_show_word_label->show();

    // 启动计时器，每1s超时一次
    this->m_timer->start(1000);
}

void Pvp::closeEvent(QCloseEvent* event)
{
    // 切换到用户主窗口
    QJsonObject send_data;
    send_data["info_type"] = "quit_midway";
    send_data["username"] = username;
    m_tcp.sendData(send_data);
    emit change_to_user_mainwindow();
}

void Pvp::init(QString* get_words, QString _username, QString _opponent)
{
    // 初始化设定
    this->current_round = 1;
    this->cost_time = 0;
    this->username = _username;
    this->opponent = _opponent;
    for(int i = 0; i < 5; i++)
    {
        words[i] = get_words[i];
    }
    this->showInfo();
}


void Pvp::on_pvp_confirm_pushButton_clicked()
{
    QString input_word = ui->pvp_input_word_lineEdit->text();
    // 输入框清空
    ui->pvp_input_word_lineEdit->clear();

    // 判断输入是否正确
    if (input_word == ui->pvp_show_word_label->text())
    {

        // 判断是否已经通过当前关卡
        if (this->current_round == 5)
        {
            QJsonObject send_data;
            QJsonObject receive_data;
            int add_exp;
            send_data["info_type"] = "end_pvp";
            send_data["username"] = username;
            receive_data = m_tcp.sendData(send_data);
            if(receive_data["win"].toBool())
            {
                if(50 - this->cost_time > 0)
                    add_exp = 100 - this->cost_time;
                else
                    add_exp = 50;
                QMessageBox::StandardButton result = QMessageBox::information(this, "提示", "挑战成功！", QMessageBox::Ok);
                if(result == QMessageBox::Ok)
                {
                    emit change_to_user_mainwindow();
                }
            }
            else
            {
                add_exp = 0;
                QMessageBox::StandardButton result = QMessageBox::information(this, "提示", "挑战失败！", QMessageBox::Ok);
                if(result == QMessageBox::Ok)
                {
                    emit change_to_user_mainwindow();
                }
            }

            // 更新闯关者数据
            emit this->passed(add_exp, 0, 0);
        }
        // 继续进行下一轮
        else
        {
            this->current_round++;
            this->showInfo();
        }
    }
    else
    {
        QMessageBox::StandardButton result = QMessageBox::information(this, "提示", "挑战失败！", QMessageBox::Ok);
        if(result == QMessageBox::Ok)
        {
            emit change_to_user_mainwindow();
        }
    }
}

