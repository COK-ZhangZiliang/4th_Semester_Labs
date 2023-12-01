#include "add_word.h"
#include "ui_add_word.h"
#include "word_database.h"
#include <QMessageBox>

Add_Word::Add_Word(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Add_Word)
{
    ui->setupUi(this);

    // 使用正则表达式限制输入只能为大小写英文字母
    QRegularExpression regExp("[A-Za-z]+");
    QValidator* validator = new QRegularExpressionValidator(regExp, this);
    ui->addword_lineEdit->setValidator(validator);
}

Add_Word::~Add_Word()
{
    delete ui;
}

void Add_Word::on_confirm_pushButton_clicked()
{
    QString word = ui->addword_lineEdit->text();
    if(word != "")
    {
        Word_Database word_db;
        if(word_db.addWord(word))
        {
            QMessageBox::information(this, "提示", "添加成功!");
            int addExp = word.size() * 5;
            emit added(addExp, 0, 1);
        }
        else
        {
            QMessageBox::critical(this, "错误", "单词已存在!");
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "请输入单词!");
    }
    ui->addword_lineEdit->clear();
}

void Add_Word::closeEvent(QCloseEvent* event)
{
    // 切换到用户主窗口
    emit change_to_user_mainwindow();
}

