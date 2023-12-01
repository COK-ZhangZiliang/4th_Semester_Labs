#include "user_database.h"
#include <QJsonArray>

// 构造函数
User_Database::User_Database()
{
    // 获取user连接
    m_db = QSqlDatabase::database("user");
    if (!m_db.open())
    {
        qDebug() << "Failed to get user connection.";
    }
}

// 析构函数
User_Database::~User_Database()
{
    // 关闭数据库连接
    m_db.close();
}

// 数据库初始化
bool User_Database::init()
{
    QSqlDatabase db;
    // 加载数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE", "user");
    // 设置数据库文件名
    db.setDatabaseName("user.db");
    // 打开数据库
    if (!db.open())
    {
        qDebug() << "Failed to connect database.";
        return false;
    }
    // 如果没有用户表，则创建用户表
    QSqlQuery query(db);
    if (!query.exec("create table if not exists user("
                    "username varchar(30) primary key," // 用户名
                    "password varchar(30),"             // 密码
                    "role int,"                         // 角色
                    "level int,"                        // 等级
                    "experience int,"                   // 经验
                    "questionCount int,"                // 出题数目
                    "passedLevels int,"                 // 已闯关卡数
                    "get_back_pwd_que varchar(200),"    // 找回密码问题
                    "get_back_pwd_ans varchar(200))"))  // 找回密码答案
        qDebug() << query.lastError();
    return true;
}

// 按照用户名查询用户，查询到返回true
bool User_Database::findUser(const QString& username)
{
    QSqlQuery query(m_db);
    query.prepare("select * from user where username = :username");
    query.bindValue(":username", username);
    if (!query.exec())
    {
        qDebug() << "Failed to find." << query.lastError();
    }
    else if (query.next())
    {
        return true;
    }
    return false;
}

// 输出数据库所有记录
void User_Database::printAllRecords() const
{
    QSqlQuery query(m_db);
    if (!query.exec("select * from user"))
    {
        qDebug() << "Failed to print." << query.lastError();
        return;
    }
    while (query.next())
    {
        for (int i = 0; i < 7; i++)
        {
            qDebug() << query.value(i).toString();
        }
    }
}

// 清除数据库信息
void User_Database::clearAllRecords()
{
    QSqlQuery query(m_db);
    if (!query.exec("delete from user"))
    {
        qDebug() << "Failed to clear." << query.lastError();
    }
}

// 根据用户信息向数据库添加用户
void User_Database::addUser(const User& user, int role, QString question, QString answer)
{
    QSqlQuery query(m_db);
    query.prepare("insert into user values(:username, :password, :role, 0, 0, 0, 0, :get_back_pwd_que, :get_back_pwd_ans)");
    query.bindValue(":username", user.getUsername());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":role", role);
    query.bindValue(":get_back_pwd_que", question);
    query.bindValue(":get_back_pwd_ans", answer);
    if (!query.exec())
    {
        qDebug() << "Failed to add user." << query.lastError();
    }
}

// 检验用户名和密码是否匹配
bool User_Database::checkPassword(const QString& username, const QString& password)
{
    QSqlQuery query(m_db);
    query.prepare("select * from user where username = :username and password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (!query.exec())
    {
        qDebug() << "Failed to check." << query.lastError();
    }
    else if (query.next())
    {
        return true;
    }
    return false;
}

// 更新用户信息
void User_Database::updateUser(const QString& username, const int& level, const int& experience, const int& questionCount, const int& passedLevels)
{
    QSqlQuery query(m_db);
    query.prepare("update user set level = :level, experience = :experience, questionCount = :questionCount, passedLevels = :passedLevels where username = :username");
    query.bindValue(":username", username);
    query.bindValue(":level", level);
    query.bindValue(":experience", experience);
    query.bindValue(":questionCount", questionCount);
    query.bindValue(":passedLevels", passedLevels);
    if (!query.exec())
    {
        qDebug() << "Failed to update." << query.lastError();
    }
}

// 获取用户信息
void User_Database::get_User(const QString& username, int& role, int& level, int& experience, int& questionCount, int& passedLevels)
{
    QSqlQuery query(m_db);
    query.prepare("select * from user where username = :username");
    query.bindValue(":username", username);
    if (!query.exec())
    {
        qDebug() << "Failed to find." << query.lastError();
    }
    else if (query.next())
    {
        role = query.value(2).toInt();
        level = query.value(3).toInt();
        experience = query.value(4).toInt();
        questionCount = query.value(5).toInt();
        passedLevels = query.value(6).toInt();
    }
}

// 向json文件中写入信息
bool User_Database::writeToJsonFile(QJsonArray& json) const
{
    QSqlQuery query(m_db);
    query.prepare("select * from user");
    if (!query.exec())
    {
        qDebug() << "Failed to write to json." << query.lastError();
        return false;
    }
    else
    {
        while(query.next())
        {
            QJsonObject user;
            user["username"] = query.value(0).toString();
            user["password"] = query.value(1).toString();
            user["role"] = query.value(2).toInt();
            user["level"] = query.value(3).toInt();
            user["experience"] = query.value(4).toInt();
            user["questionCount"] = query.value(5).toInt();
            user["passedLevels"] = query.value(6).toInt();
            user["get_back_pwd_que"] = query.value(7).toString();
            user["get_back_pwd_ans"] = query.value(8).toString();
            json.append(user);
        }
    }
    return true;
}

void User_Database::resetPassword(const QString username, const QString password)const
{
    QSqlQuery query(m_db);
    query.prepare("update user set password = :password where username = :username");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (!query.exec())
    {
        qDebug() << "Failed to update." << query.lastError();
    }
}
