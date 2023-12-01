#ifndef MATCHING_H
#define MATCHING_H

#include <QMainWindow>
#include <QTimer>

namespace Ui
{
    class Matching;
}

class Matching : public QMainWindow
{
    Q_OBJECT

public:
    explicit Matching(QWidget* parent = nullptr);
    ~Matching();

signals:
    // 取消匹配
    void cancel();

private slots:
    void on_cancel_pushButton_clicked();

    void closeEvent(QCloseEvent* event);

private:
    Ui::Matching* ui;
    QTimer* m_timer;
    int index;
    QString label_content[3] = {"匹配中.", "匹配中..", "匹配中..."};
};

#endif // MATCHING_H
