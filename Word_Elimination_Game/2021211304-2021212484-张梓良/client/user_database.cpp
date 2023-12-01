#include "user_database.h"
#include <QJsonArray>

User_Database::User_Database()
{
    // 获取user连接
    m_db = QSqlDatabase::database("user");
    if (!m_db.open())
    {
        qDebug() << "Failed to get user connection.";
    }
}

User_Database::~User_Database()
{
    // 关闭数据库连接
    //m_db.close();
}

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

bool User_Database::findUser(const QString& username)
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "findUser";
    send_data["username"] = username;
    receive_data = m_tcp.sendData(send_data);
    if(receive_data["received"].toBool())
        return receive_data["user_exist"].toBool();
    else
        return false;
}

void User_Database::addUser(const User& user, int role, QString question, QString answer)
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "addUser";
    send_data["username"] = user.getUsername();
    send_data["password"] = user.getPassword();
    send_data["level"] = user.getLevel();
    send_data["role"] = role;
    send_data["question"] = question;
    send_data["answer"] = answer;
    receive_data = m_tcp.sendData(send_data);
}

// 检验用户名和密码是否匹配
int User_Database::checkPassword(const QString& username, const QString& password)
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "checkPassword";
    send_data["username"] = username;
    send_data["password"] = password;
    receive_data = m_tcp.sendData(send_data);
    if(receive_data["received"].toBool())
        return receive_data["status"].toInt();
    qDebug() << "Disconnected to the server.";
    return -1;
}

// 更新用户信息
void User_Database::updateUser(const QString username, const int level, const int experience, const int questionCount, const int passedLevels)const
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "updateUser";
    send_data["username"] = username;
    send_data["level"] = level;
    send_data["experience"] = experience;
    send_data["questionCount"] = questionCount;
    send_data["passedLevels"] = passedLevels;
    m_tcp.sendData(send_data);
}

// 获取用户信息
void User_Database::getUser(const QString& username, int& role, int& level, int& experience, int& questionCount, int& passedLevels)const
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "getUser";
    send_data["username"] = username;
    receive_data = m_tcp.sendData(send_data);
    if(receive_data["received"].toBool())
    {
        role = receive_data["role"].toInt();
        level = receive_data["level"].toInt();
        experience = receive_data["experience"].toInt();
        questionCount = receive_data["questionCount"].toInt();
        passedLevels = receive_data["passedLevels"].toInt();
    }
    else
        qDebug() << "Disconnected to the server.";
}

void User_Database::get_all_userInfo()
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "get_all_userInfo";
    receive_data = m_tcp.sendData(send_data);
    if(receive_data["received"].toBool())
    {
        QSqlQuery query(m_db);
        // 先清空数据库
        if (!query.exec("delete from user"))
        {
            qDebug() << "Failed to clear." << query.lastError();
        }
        QJsonArray array = receive_data["all_userInfo"].toArray();
        for(int i = 0; i < array.size(); i++)
        {
            QJsonObject object = array[i].toObject();
            query.prepare("insert into user values(:username, :password, :role, :level, :experience, :questionCount, :passedLevels, :get_back_pwd_que, :get_back_pwd_ans)");
            query.bindValue(":username", object["username"].toString());
            query.bindValue(":password", object["password"].toString());
            query.bindValue(":role", object["role"].toInt());
            query.bindValue(":level", object["level"].toInt());
            query.bindValue(":experience", object["experience"].toInt());
            query.bindValue(":questionCount", object["questionCount"].toInt());
            query.bindValue(":passedLevels", object["passedLevels"].toInt());
            query.bindValue(":get_back_pwd_que", object["get_back_pwd_que"].toString());
            query.bindValue(":get_back_pwd_ans", object["get_back_pwd_ans"].toString());
            if (!query.exec())
            {
                qDebug() << "Failed to add user." << query.lastError();
            }
        }
    }
    else
        qDebug() << "Disconnected to the server.";
}

bool User_Database::checkAns(QString username, QString ans)
{
    QSqlQuery query(m_db);
    query.prepare("select * from user where username = :username and get_back_pwd_ans = :get_back_pwd_ans");
    query.bindValue(":username", username);
    query.bindValue(":get_back_pwd_ans", ans);
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

QString User_Database::getQue(QString username)
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
        return query.value(7).toString();
    }
    return "";
}

// 重置密码
void User_Database::resetPassword(const QString username, const QString password)const
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "resetPassword";
    send_data["username"] = username;
    send_data["password"] = password;
    m_tcp.sendData(send_data);
}

