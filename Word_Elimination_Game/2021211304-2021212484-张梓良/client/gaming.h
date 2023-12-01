#ifndef GAMING_H
#define GAMING_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>

namespace Ui
{
    class Gaming;
}

class Gaming : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gaming(QWidget* parent = nullptr);
    ~Gaming();

    // 展示单词
    void showInfo();
    // 覆写closeEvent函数
    void closeEvent(QCloseEvent* event);
    // 初始化
    void init(int level);

signals:
    // 闯关成功,更新用户数据
    void passed(int addExp, int new_passedLevels, int new_questionCount);
    // 切换到用户主窗口
    void change_to_user_mainwindow();

private slots:
    void on_confirm_pushButton_clicked();

private:
    Ui::Gaming* ui;

    QTimer* m_timer; // 倒计时
    int cost_time; // 花费时间
    int rest_time; // 剩余时间
    int current_level; // 当前是第几关
    int current_round; // 当前是第几轮
};

#endif // GAMING_H
