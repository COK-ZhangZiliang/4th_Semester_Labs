#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <QObject>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class Tcp_Connection: public QObject
{
    Q_OBJECT
public:
    Tcp_Connection(QString _ip = "127.0.0.1", unsigned short _port = 8888);
    ~Tcp_Connection();

    // 向服务器发送数据，并返回服务器发回的数据
    QJsonObject sendData(const QJsonObject& send_data);

private:
    QString ip;
    unsigned short port;
    QTcpSocket* socket;
};

extern Tcp_Connection m_tcp;

#endif // TCP_CONNECTION_Hd_
