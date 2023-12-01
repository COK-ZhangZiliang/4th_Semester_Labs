#ifndef USER_DATABASE_H
#define USER_DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "user.h"

class User_Database
{
public:
    // 构造函数
    User_Database();
    // 析构函数
    ~User_Database();

    // 数据库初始化
    static bool init();
    // 按照用户名查询用户，查询到返回true
    bool findUser(const QString& username);
    // 输出数据库所有记录
    void printAllRecords() const;
    // 清除数据库信息
    void clearAllRecords();
    // 根据用户信息向数据库添加用户
    void addUser(const User& user, int role, QString question, QString answer);
    // 检验用户名和密码是否匹配
    bool checkPassword(const QString& username, const QString& password);
    // 更新用户信息
    void updateUser(const QString& username, const int& level, const int& experience, const int& questionCount, const int& passedLevels);
    // 获取用户信息
    void get_User(const QString& username, int& role, int& level, int& experience, int& questionCount, int& passedLevels);
    // 向json文件中写入所有用户信息
    bool writeToJsonFile(QJsonArray& json) const;
    // 重置密码
    void resetPassword(const QString username, const QString password)const;

private:
    // 用户数据库对象
    QSqlDatabase m_db;
};

#endif // USER_DATABASE_H
