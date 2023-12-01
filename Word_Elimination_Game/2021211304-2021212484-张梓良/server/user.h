#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

class User
{
public:
    User(QString username, QString password, int level);

    // 获取用户名
    QString getUsername() const;
    // 获取用户等级
    int getLevel() const;
    // 获取用户密码
    QString getPassword() const;

    // 向json中写入用户信息
    void writeToJson(QJsonObject& json) const;
    // 从json中读入用户信息
    void readFromJson(const QJsonObject& json);

private:
    QString m_username; // 用户名
    QString m_password; // 密码
    int m_level;        // 等级
};

#endif // USER_H
