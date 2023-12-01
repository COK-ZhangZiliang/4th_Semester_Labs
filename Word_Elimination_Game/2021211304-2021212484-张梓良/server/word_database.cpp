#include "word_database.h"

// 构造函数
Word_Database::Word_Database()
{
    // 获取word连接
    m_db = QSqlDatabase::database("word");
    if (!m_db.open())
    {
        qDebug() << "Failed to get word connection.";
    }
}

// 析构函数
Word_Database::~Word_Database()
{
    // 关闭数据库连接
    m_db.close();
}

// 数据库初始化
bool Word_Database::init()
{
    QSqlDatabase db;
    // 加载数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE", "word");
    // 设置数据库文件名
    db.setDatabaseName("word.db");
    // 打开数据库
    if (!db.open())
    {
        qDebug() << "Failed to connect database.";
        return false;
    }
    // 如果没有用户表，则创建用户表
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS word("
                    "word varchar(30) primary key," // 单词
                    "len int)"))                    // 单词长度
        qDebug() << query.lastError();
    return true;
}

// 查询单词
bool Word_Database::findWord(const QString& word)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM word WHERE word = :word");
    query.bindValue(":word", word);
    if (!query.exec())
    {
        qDebug() << "Failed to find word." << query.lastError();
    }
    else if (query.next())
    {
        return true;
    }
    return false;
}

// 输出数据库所有记录
void Word_Database::printAllRecords() const
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM word"))
    {
        qDebug() << "Failed to print word." << query.lastError();
        return;
    }
    while (query.next())
    {
        for (int i = 0; i < 1; i++)
        {
            qDebug() << query.value(i).toString();
        }
    }
}

// 清除数据库信息
void Word_Database::clearAllRecords()
{
    QSqlQuery query(m_db);
    if (!query.exec("DELETE FROM word"))
    {
        qDebug() << "Failed to clear." << query.lastError();
    }
}

// 添加单词
void Word_Database::addWord(const QString& word)
{
    QSqlQuery query(m_db);
    query.prepare("insert into word values(:word, :len)");
    query.bindValue(":word", word);
    query.bindValue(":len", word.size());
    if (!query.exec())
    {
        qDebug() << "Failed to add word." << query.lastError();
    }
}

// 获取指定长度范围的单词
QString Word_Database::getWord(int len1, int len2)
{
    QSqlQuery query(m_db);
    query.prepare("select * from word where len >= :len1 and len <= :len2 order by random() limit 1");
    query.bindValue(":len1", len1);
    query.bindValue(":len2", len2);
    if (!query.exec())
    {
        qDebug() << "Failed to get word." << query.lastError();
        return "";
    }
    else
    {
        if(query.next())
            return query.value(0).toString();
        else
        {
            qDebug() << "There is no word that satisfy the condition in the word database.";
            return "";
        }
    }
}
