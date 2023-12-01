#include "tcp_connection.h"

Tcp_Connection::Tcp_Connection(QString _ip, unsigned short _port): ip(_ip), port(_port)
{
    socket = new QTcpSocket();
    socket->connectToHost(ip, port);
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Failed to connect to the server.";
    }
}

Tcp_Connection::~Tcp_Connection()
{
    delete socket;
}

QJsonObject Tcp_Connection::sendData(const QJsonObject& send_data)
{
    QJsonObject receive_data;
    if(socket->state() == QTcpSocket::ConnectedState)
    {
        // 将要发送的json数据流转换为byteArray类型
        QByteArray byteArray = QJsonDocument(send_data).toJson();
        // 发送数据
        socket->write(byteArray);
        // 手动清空缓冲区
        socket->flush();

        // 接收服务器发来的数据
        if(socket->waitForReadyRead(5000))
        {
            byteArray = socket->readAll();
            receive_data = QJsonDocument::fromJson(byteArray).object();
            receive_data["received"] = true;
        }
        else
        {
            qDebug() << "Nothing come back.";
            receive_data["received"] = false;
        }
    }
    else
    {
        qDebug() << "Disconneted to the server.";
        socket->connectToHost(ip, port);
        if(!socket->waitForConnected(5000))
        {
            qDebug() << "Failed to connect to the server.";
        }
        receive_data["received"] = false;
    }
    return receive_data;
}

Tcp_Connection m_tcp;
