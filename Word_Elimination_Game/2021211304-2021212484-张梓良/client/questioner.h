#ifndef QUESTIONER_H
#define QUESTIONER_H

#include "user.h"
#include <QJsonObject>

class Questioner : public User
{
public:
    Questioner(QString username, QString password, int level, int questionCount);

    int getQuestionCount() const;
    void writeToJson(QJsonObject& json) const;
    void readFromJson(const QJsonObject& json);

private:
    int m_questionCount;
};

#endif // QUESTIONER_H
