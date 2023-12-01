#include "questioner.h"

Questioner::Questioner(QString username, QString password, int level, int questionCount)
    : User(username, password, level), m_questionCount(questionCount)
{}

int Questioner::getQuestionCount() const
{
    return m_questionCount;
}

void Questioner::writeToJson(QJsonObject& json) const
{
    User::writeToJson(json);
    json["question_count"] = m_questionCount;
}

void Questioner::readFromJson(const QJsonObject& json)
{
    User::readFromJson(json);
    m_questionCount = json["question_count"].toInt();
}
