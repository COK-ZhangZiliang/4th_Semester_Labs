#include "word_database.h"

bool Word_Database::addWord(const QString& word)
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "addWord";
    send_data["word"] = word;
    receive_data = m_tcp.sendData(send_data);
    if(receive_data["received"].toBool())
    {
        if(receive_data["word_exist"].toBool())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    qDebug() << "Disconnected to the server.";
    return false;
}

QString Word_Database::getWord(int min_len, int max_len)
{
    QJsonObject send_data;
    QJsonObject receive_data;
    send_data["info_type"] = "getWord";
    send_data["min_len"] = min_len;
    send_data["max_len"] = max_len;
    receive_data = m_tcp.sendData(send_data);
    if(receive_data["received"].toBool())
    {
        return receive_data["word"].toString();
    }
    qDebug() << "Disconnected to the server.";
    return "";
}
