#include "tcp_connection.h"

Tcp_Connection::Tcp_Connection(unsigned short port)
{
    m_server = new QTcpServer;
    m_server->listen(QHostAddress::Any, port);
    this->socket_user.clear();
    this->connections.clear();
    this->waitList.clear();
    this->pvp.clear();
    this->win.clear();

    // 检测是否有新的客户端连接
    connect(m_server, &QTcpServer::newConnection, this, [ = ]()
    {
        qDebug() << "A new connection arrived.";
        QTcpSocket* new_tcp = m_server->nextPendingConnection();
        // 将新的连接存入连接向量中
        connections.push_back(new_tcp);

        // 检测是否有客户端数据
        connect(new_tcp, &QTcpSocket::readyRead, this, [ = ]()
        {
            // 判断是哪个客户端发出了数据
            QTcpSocket* current_client = qobject_cast<QTcpSocket*>(sender());
            // 获取json文件
            QByteArray array = current_client->readAll();
            QJsonObject receive = QJsonDocument::fromJson(array).object();
            QString info_type = receive["info_type"].toString();

            // 根据收到的客户端信息类型向客户端回复对应json文件
            QJsonObject reply;
            User_Database user_db;
            Word_Database word_db;
            // 检测用户名和密码是否匹配
            if(info_type == "checkPassword")
            {
                qDebug() << "checkPassword";
                if(user_db.checkPassword(receive["username"].toString(), receive["password"].toString()))
                {
                    int flag = 1;
                    reply["status"] = 1;
                    // 判断是否已经在线
                    for(int i = 0; i < connections.size(); i++)
                    {
                        if(connections[i] != current_client && this->socket_user[connections[i]] == receive["username"].toString())
                        {
                            reply["status"] = 0;
                            flag = 0;
                        }
                    }
                    // 创建新的连接到用户之间的映射
                    if(flag)
                    {
                        socket_user[current_client] = receive["username"].toString();
                    }
                }
                else
                {
                    reply["status"] = -1;
                }
            }

            // 获取用户信息
            else if(info_type == "getUser")
            {
                qDebug() << "getUser";
                int role, level, experience, questionCount, passedLevels;
                user_db.get_User(receive["username"].toString(), role, level, experience, questionCount, passedLevels);
                reply["role"] = role;
                reply["level"] = level;
                reply["experience"] = experience;
                reply["questionCount"] = questionCount;
                reply["passedLevels"] = passedLevels;
            }

            // 查找用户
            else if(info_type == "findUser")
            {
                qDebug() << "findUser";
                if(user_db.findUser(receive["username"].toString()))
                {
                    reply["user_exist"] = true;
                }
                else
                {
                    reply["user_exist"] = false;
                }
            }

            // 添加用户
            else if(info_type == "addUser")
            {
                qDebug() << "addUser";
                User user(receive["username"].toString(), receive["password"].toString(), receive["level"].toInt());
                user_db.addUser(user, receive["role"].toInt(), receive["question"].toString(), receive["answer"].toString());
            }

            // 更新用户信息
            else if(info_type == "updateUser")
            {
                qDebug() << "updateUser";
                user_db.updateUser(receive["username"].toString(), receive["level"].toInt(), receive["experience"].toInt(), receive["questionCount"].toInt(), receive["passedLevels"].toInt());
            }

            // 获取所有用户信息
            else if(info_type == "get_all_userInfo")
            {
                qDebug() << "get_all_userInfo";
                QJsonArray array;
                if(user_db.writeToJsonFile(array))
                {
                    qDebug() << "Succeed in geting all users' information.";
                    reply["all_userInfo"] = array;
                }
                else
                {
                    qDebug() << "Failed in geting all users' information.";
                }
            }

            // 添加单词
            else if(info_type == "addWord")
            {
                qDebug() << "addWord";
                // 判断单词是否已经存在
                if(!word_db.findWord(receive["word"].toString()))
                {
                    word_db.addWord(receive["word"].toString());
                    reply["word_exist"] = false;
                }
                else
                {
                    reply["word_exist"] = true;
                }
            }

            // 随机获取满足条件的单词
            else if(info_type == "getWord")
            {
                qDebug() << "getWord";
                reply["word"] = word_db.getWord(receive["min_len"].toInt(), receive["max_len"].toInt());
            }

            // pvp对战
            else if(info_type == "pvp")
            {
                bool pvp_success = false;
                qDebug() << "pvp";
                QString user = receive["username"].toString();
                int flag = 0;
                if(pvp.find(user) != pvp.end())
                {
                    // 已经成功匹配
                    qDebug() << "in pvp";
                    pvp_success = true;
                    reply["opponent"] = pvp[user];
                }
                for(int i = 0; i < waitList.size(); i++)
                {
                    if(waitList[i] == user)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    waitList.push_back(user);
                    // 匹配成功
                    if(waitList.size() >= 2)
                    {
                        qDebug() << "matching success";
                        pvp_success = true;
                        waitList.removeOne(user);
                        QString opponent = waitList[0];
                        reply["opponent"] = opponent;
                        waitList.pop_front();
                        pvp[user] = opponent;
                        pvp[opponent] = user;

                        // 获取10个不同的单词
                        for(int i = 0; i < 5;)
                        {
                            QString word = word_db.getWord(4, 8);
                            int flag = 0; // 判重标志
                            qDebug() << word;
                            for(int j = 0; j < i; j++)
                            {
                                if(word == words[user][j])
                                {
                                    flag = 1;
                                    break;
                                }
                            }
                            if(flag == 0)
                            {
                                words[user].push_back(word);
                                words[opponent].push_back(word);
                                i++;
                            }
                        }
                    }
                }
                if(pvp_success)
                {
                    qDebug() << "pvp success";
                    reply["pvp"] = true;
                    QJsonArray array;
                    QJsonObject object;
                    for(int i = 0; i < 5; i++)
                    {
                        object["word"] = words[user][i];
                        array.append(object);
                    }
                    reply["words"] = array;
                }
                else
                {
                    reply["pvp"] = false;
                }
            }

            // 取消匹配
            else if(info_type == "cancel_pvp")
            {
                qDebug() << "cancel_pvp";
                QString user = receive["username"].toString();
                waitList.removeOne(user);
            }

            // 对战结束
            else if(info_type == "end_pvp")
            {
                QString user = receive["username"].toString();
                qDebug() << "end_pvp";
                QString opponent = pvp[user];
                pvp.erase(pvp.find(user));
                if(win.find(opponent) != win.end())
                {
                    win.erase(win.find(opponent));
                    reply["win"] = false;
                }
                else
                {
                    win[user] = true;
                    reply["win"] = true;
                }
            }

            // 中途退出pvp
            else if(info_type == "quit_midway")
            {
                QString user = receive["username"].toString();
                qDebug() << "quit_midway";
                if(pvp.find(user) != pvp.end())
                    pvp.erase(pvp.find(user));
            }

            // 重置密码
            else if(info_type == "resetPassword")
            {
                qDebug() << "resetPassword";
                user_db.resetPassword(receive["username"].toString(), receive["password"].toString());
            }

            // 将要发送的json数据流转换为byteArray类型
            QByteArray byteArray = QJsonDocument(reply).toJson();
            // 发送数据
            current_client->write(byteArray);
            // 手动清空缓冲区
            current_client->flush();

        });

        // 客户端断开连接
        connect(new_tcp, &QTcpSocket::disconnected, this, [ = ]()
        {
            // 判断是哪个客户端请求断开连接
            qDebug() << "A host disconnected.";
            QTcpSocket* current_client = qobject_cast<QTcpSocket*>(sender());
            connections.removeOne(current_client);
            current_client->deleteLater();
        });
    });
}

Tcp_Connection::~Tcp_Connection()
{
    for(int i = 0; i < connections.size(); i++)
    {
        if(connections[i]->state() == QTcpSocket::ConnectedState)
        {
            connections[i]->disconnectFromHost();
        }
    }
    delete m_server;
}

void Tcp_Connection::listen(const QHostAddress& address, quint16 port)
{
    m_server->listen(address, port);
}
