#ifndef WORD_DATABASE_H
#define WORD_DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>

class Word_Database
{
public:
    // 构造函数
    Word_Database();
    // 析构函数
    ~Word_Database();

    // 数据库初始化
    static bool init();
    // 向数据库中添加单词
    void addWord(const QString& word);
    // 向数据库中查询单词
    bool findWord(const QString& word);
    // 输出数据库所有记录
    void printAllRecords() const;
    // 清除数据库信息
    void clearAllRecords();
    // 获取指定长度范围的单词
    QString getWord(int len1, int len2);

private:
    // 用户数据库对象
    QSqlDatabase m_db;
};

#endif // WORD_DATABASE_H
