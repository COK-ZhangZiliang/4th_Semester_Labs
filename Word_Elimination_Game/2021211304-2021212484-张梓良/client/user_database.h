#ifndef USER_DATABASE_H
#define USER_DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "user.h"
#include "tcp_connection.h"

class User_Database
{
public:
    User_Database();
    ~User_Database();

    // 初始化数据库
    static bool init();
    // 按照用户名查询用户，查询到返回true
    bool findUser(const QString& username);
    // 根据用户信息向数据库添加用户
    void addUser(const User& user, int role, QString question, QString answer);
    // 检验用户名和密码是否匹配
    int checkPassword(const QString& username, const QString& password);
    // 更新用户信息
    void updateUser(const QString username, const int level, const int experience, const int questionCount, const int passedLevels)const;
    // 获取用户信息
    void getUser(const QString& username, int& role, int& level, int& experience, int& questionCount, int& passedLevels)const;
    // 获取所有用户信息
    void get_all_userInfo();
    // 检验重置密码答案是否正确
    bool checkAns(QString usrname, QString ans);
    // 获取重置密码的问题
    QString getQue(QString username);
    // 更新密码
    void resetPassword(const QString username, const QString password)const;

private:
    QSqlDatabase m_db;
};

#endif // USER_DATABASE_H
