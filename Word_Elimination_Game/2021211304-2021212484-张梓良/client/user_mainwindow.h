#ifndef USER_MAINWINDOW_H
#define USER_MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QLabel>
#include "add_word.h"
#include "gaming.h"
#include "pvp.h"
#include "user_database.h"
#include "tcp_connection.h"
#include "matching.h"

#define CHALLENGER 0
#define QUESTIONER 1
#define LEVEL 1
#define PASSED_LEVELS 3
#define QUESTION_COUNT 3

namespace Ui
{
    class User_MainWindow;
}

class User_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit User_MainWindow(QWidget* parent = nullptr);
    ~User_MainWindow();

    // 对闯关者根据关键字key排序
    void sort_challengeer(int key, QTableView* tableView);

    // 对出题者根据关键字key排序
    void sort_questioner(int key, QTableView* tableView);

    // 查询用户
    void search();

    // 覆写closeEvent函数
    void closeEvent(QCloseEvent* event);

    // 获取状态栏信息
    void statusbar_info(const QString& username, const int& role, const int& level, const int& experience, const int& questionCount, const int& passedLevels);

    // 设置按钮是否可以点击
    void setPushbutton(int role);
signals:
    // 关闭所有窗口
    void close_all();
    // 开始新游戏
    void begin_new_game();
    // 继续游戏
    void continue_game();
    // 开始出题
    void begin_add_word();
    // 更新用户信息
    void update_info(int addExp, int new_passedLevels, int new_questionCount);
    // 开始pvp对战
    void begin_pvp();

private slots:
    void on_new_game_pushButton_clicked();

    void on_continue_game_pushButton_clicked();

    void on_add_words_pushButton_clicked();

    void on_multi_player_pushButton_clicked();

private:
    Ui::User_MainWindow* ui;
    QLabel username_label;
    QLabel role_label;
    QLabel level_label;
    QLabel exp_label;
    QLabel questioncnt_label;
    QLabel passedlevels_label;
    Gaming* game;
    Pvp* pvp;
    Matching* matching;
    Add_Word* add_word;
    QTimer*  m_timer;
    QTimer*  pvp_timer;
    User_Database user_db;
    int passedlevels; // 用户已闯关卡数
    QString username;
    bool matching_success;
};

#endif // USER_MAINWINDOW_H
