#include "user.h"

User::User(QString username, QString password, int level)
    : m_username(username), m_password(password), m_level(level)
{}

QString User::getUsername() const
{
    return m_username;
}

int User::getLevel() const
{
    return m_level;
}

QString User::getPassword() const
{
    return m_password;
}

void User::writeToJson(QJsonObject& json) const
{
    json["username"] = m_username;
    json["password"] = m_password;
    json["level"] = m_level;
}

void User::readFromJson(const QJsonObject& json)
{
    m_username = json["username"].toString();
    m_password = json["password"].toString();
    m_level = json["level"].toInt();
}
