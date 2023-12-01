#ifndef PVP_H
#define PVP_H

#include <QMainWindow>
#include <QTimer>
#include "tcp_connection.h"

namespace Ui
{
    class Pvp;
}

class Pvp : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pvp( QWidget* parent = nullptr);
    ~Pvp();

    // 初始化
    void init(QString* get_words, QString _username, QString _opponent);
    // 关闭窗口
    void closeEvent(QCloseEvent* event);
    // 显示信息
    void showInfo();

signals:
    // 切换到用户主界面
    void change_to_user_mainwindow();
    // 闯关成功
    void passed(int addExp, int new_passedLevels, int new_questionCount);

private slots:
    void on_pvp_confirm_pushButton_clicked();

private:
    Ui::Pvp* ui;
    QTimer* m_timer;
    int current_round;
    int rest_time;
    int cost_time;
    QString words[5]; // 获取到的单词
    QString username;
    QString opponent;
};

#endif // PVP_H
