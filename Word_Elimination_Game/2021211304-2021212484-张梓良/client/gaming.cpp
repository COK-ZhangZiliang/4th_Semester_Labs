#include "gaming.h"
#include "ui_gaming.h"
#include "word_database.h"
#include <QRegularExpressionValidator>

const int min_len[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};      // 每关最小单词长度
const int max_len[16] = {0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};   // 每关最大单词长度
const int total_rounds[16] = {0, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6};    // 每关轮数
const int round_time[16] = {0, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 3, 3};      // 每轮时间
QString words[10]; // 已选单词

Gaming::Gaming(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Gaming)
{
    ui->setupUi(this);

    this->m_timer = new QTimer(this);
    // 使用正则表达式限制输入只能为大小写英文字母
    QRegularExpression regExp("[A-Za-z]+");
    QValidator* validator = new QRegularExpressionValidator(regExp, this);
    ui->input_word_lineEdit->setValidator(validator);

    connect(m_timer, &QTimer::timeout, this, [ = ]
    {
        ui->rest_time_progressBar->setValue(--rest_time);

        // 判断是否还剩余时间
        if(!rest_time)
        {
            m_timer->stop();
            // 单词消失
            ui->show_word_label->hide();
            // 允许用户输入
            ui->input_word_lineEdit->setEnabled(true);
            ui->input_word_lineEdit->setFocus();
            cost_time++;
        }
    });
}

Gaming::~Gaming()
{
    delete ui;
}

void Gaming::showInfo()
{
    ui->input_word_lineEdit->setEnabled(false);
    this->rest_time = round_time[this->current_level];
    ui->rest_time_progressBar->setMaximum(this->rest_time);

    // 从单词库抓取符合条件且没有重复的单词
    Word_Database word_db;
    QString word;
    while(1)
    {
        qDebug() << "duplicated";
        word = word_db.getWord(min_len[current_level], max_len[current_level]);
        int flag = 0; // 判重标志
        for(int i = 1; i < this->current_round; i++)
        {
            if(word == words[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            break;
    }
    words[current_round] = word;

    // 显示当前关卡数、轮数
    ui->current_level_label->setText(QString("当前关卡数：%1").arg(this->current_level));
    ui->current_round_label->setText(QString("当前轮数：%1/%2").arg(this->current_round).arg(total_rounds[this->current_level]));
    ui->statusbar->addWidget(ui->current_level_label);
    ui->statusbar->addWidget(ui->current_round_label);

    // 显示单词
    ui->show_word_label->setText(word);
    ui->show_word_label->show();

    // 启动计时器，每1s超时一次
    this->m_timer->start(1000);
}


void Gaming::on_confirm_pushButton_clicked()
{
    QString input_word = ui->input_word_lineEdit->text();
    // 输入框清空
    ui->input_word_lineEdit->clear();

    // 判断输入是否正确
    if (input_word == ui->show_word_label->text())
    {

        // 判断是否已经通过当前关卡
        if (this->current_round == total_rounds[this->current_level])
        {
            // 增加闯关者经验值
            int add_exp;
            if(round_time[this->current_level] * total_rounds[this->current_level] - this->cost_time > 0)
                add_exp = this->current_level * 10 + round_time[this->current_level] * total_rounds[this->current_level] - this->cost_time;
            else
                add_exp = this->current_level * 10;

            // 更新关卡数和轮数
            this->current_level++;
            this->current_round = 1;
            qDebug() << this->current_level;

            // 更新闯关者数据
            emit this->passed(add_exp, current_level - 1, 0);

            // 询问用户是否继续闯关
            if(this->current_level <= 15)
            {
                QMessageBox::StandardButton result = QMessageBox::information(this, "提示", "闯关成功！是否继续闯关？", QMessageBox::Yes | QMessageBox::No);
                if(result == QMessageBox::Yes)
                {
                    this->showInfo();
                }
                else
                {
                    emit change_to_user_mainwindow();
                }
            }
            // 询问用户是否重新闯关
            else
            {
                QMessageBox::StandardButton result = QMessageBox::information(this, "提示", "恭喜你，已闯完所有关卡！是否重新闯关？", QMessageBox::Yes | QMessageBox::No);
                if(result == QMessageBox::Yes)
                {
                    this->showInfo();
                }
                else
                {
                    emit change_to_user_mainwindow();
                }
            }

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
        QMessageBox::StandardButton result = QMessageBox::information(this, "提示", "闯关失败！是否重闯该关？", QMessageBox::Yes | QMessageBox::No);
        if(result == QMessageBox::Yes)
        {
            this->current_round = 1;
            this->showInfo();
        }
        else
        {
            emit change_to_user_mainwindow();
        }
    }
}

void Gaming::closeEvent(QCloseEvent* event)
{
    // 切换到用户主窗口
    emit change_to_user_mainwindow();
}

void Gaming::init(int level)
{
    // 初始化设定
    this->current_level = level;
    this->current_round = 1;
    this->cost_time = 0;
    this->showInfo();
}

