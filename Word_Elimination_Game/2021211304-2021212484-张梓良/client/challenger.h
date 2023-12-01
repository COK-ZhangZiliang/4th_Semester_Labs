#ifndef CHALLENGER_H
#define CHALLENGER_H

#include "user.h"
#include <QJsonObject>

class Challenger : public User
{
public:
    Challenger(QString username, QString password, int level, int experience, int passedLevels);

    int getExperience() const;
    int getPassedLevels() const;
    void writeToJson(QJsonObject& json) const;
    void readFromJson(const QJsonObject& json);

private:
    int m_experience;
    int m_passedLevels;
};

#endif // CHALLENGER_H
