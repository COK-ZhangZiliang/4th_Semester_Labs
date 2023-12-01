#ifndef WORD_DATABASE_H
#define WORD_DATABASE_H

#include "tcp_connection.h"

class Word_Database
{
public:
    // 构造函数
    Word_Database() = default;
    // 析构函数
    ~Word_Database() = default;

    // 向数据库中添加单词
    bool addWord(const QString& word);
    // 获取指定长度范围的单词
    QString getWord(int min_len, int max_len);
};

#endif // WORD_DATABASE_H
