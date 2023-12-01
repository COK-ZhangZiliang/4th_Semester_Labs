#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QtWidgets>
#include "sign_in.h"
#include "user_database.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    User_Database::init();

    Sign_In m;
    m.show();

    return a.exec();
}
