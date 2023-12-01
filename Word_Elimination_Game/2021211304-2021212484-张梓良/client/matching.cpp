#include "matching.h"
#include "ui_matching.h"

Matching::Matching(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Matching)
{
    ui->setupUi(this);
    this->m_timer = new QTimer(this);
    this->m_timer->start(1000);
    this->index = 0;

    connect(this->m_timer, &QTimer::timeout, ui->label, [ = ]()
    {
        ui->label->setText(label_content[index]);
        index = (index + 1) % 3;
    });
}

Matching::~Matching()
{
    delete ui;
}

void Matching::on_cancel_pushButton_clicked()
{
    emit this->cancel();
}

void Matching::closeEvent(QCloseEvent* event)
{
    // 切换到用户主窗口
    emit this->cancel();
}
