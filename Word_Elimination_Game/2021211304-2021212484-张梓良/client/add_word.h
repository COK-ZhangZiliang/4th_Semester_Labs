#ifndef ADD_WORD_H
#define ADD_WORD_H

#include <QMainWindow>
#include <QValidator>
#include <QRegularExpressionValidator>

namespace Ui
{
    class Add_Word;
}

class Add_Word : public QMainWindow
{
    Q_OBJECT

public:
    explicit Add_Word(QWidget* parent = nullptr);
    ~Add_Word();

    // 覆写closeEvent函数
    void closeEvent(QCloseEvent* event);

signals:
    // 切换到用户主界面
    void change_to_user_mainwindow();
    // 单词添加成功
    void added(int addExp, int new_passedLevels, int new_questionCount);

private slots:
    void on_confirm_pushButton_clicked();

private:
    Ui::Add_Word* ui;
};

#endif // ADD_WORD_H
