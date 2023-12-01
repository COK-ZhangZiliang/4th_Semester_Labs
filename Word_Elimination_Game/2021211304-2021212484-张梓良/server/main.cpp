#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include "tcp_connection.h"
#include "user_database.h"
#include "word_database.h"
#include <QtWidgets>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    User_Database::init();
    Word_Database::init();


    Tcp_Connection server;
    server.listen();

    return a.exec();
}
