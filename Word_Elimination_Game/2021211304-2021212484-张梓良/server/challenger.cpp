#include "challenger.h"

Challenger::Challenger(QString username, QString password, int level, int experience, int passedLevels)
    : User(username, password, level), m_experience(experience), m_passedLevels(passedLevels)
{}

int Challenger::getExperience() const
{
    return m_experience;
}

int Challenger::getPassedLevels() const
{
    return m_passedLevels;
}

void Challenger::writeToJson(QJsonObject& json) const
{
    User::writeToJson(json);
    json["experience"] = m_experience;
    json["passed_levels"] = m_passedLevels;
}

void Challenger::readFromJson(const QJsonObject& json)
{
    User::readFromJson(json);
    m_experience = json["experience"].toInt();
    m_passedLevels = json["passed_levels"].toInt();
}
