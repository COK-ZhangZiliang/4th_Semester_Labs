#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <QtNetwork>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include <QMap>
#include <QSet>
#include "user_database.h"
#include "word_database.h"
#include "user.h"

class Tcp_Connection : public QObject
{
    Q_OBJECT
public:
    Tcp_Connection(unsigned short port = 8888);
    ~Tcp_Connection();

    // 监听函数
    void listen(const QHostAddress& address = QHostAddress::Any, quint16 port = 8888);

private:
    QTcpServer* m_server;  // 服务器
    QVector<QTcpSocket*> connections; // 存储所有连接的socket
    QMap<QTcpSocket*, QString> socket_user; // 存储连接和用户之间的映射关系
    QVector<QString> waitList; // 等待匹配的用户
    QMap<QString, QString> pvp; // 匹配成功的用户
    QMap<QString, QVector<QString>> words; // pvp单词库
    QMap<QString, bool> win; // 记录获胜者
};

#endif // TCP_CONNECTION_H
