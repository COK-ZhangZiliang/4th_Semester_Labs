#include "user_mainwindow.h"
#include "ui_user_mainwindow.h"
#include "user_database.h"
#include <QtSql>
#include <QtWidgets>
#include <QTabWidget>

User_MainWindow::User_MainWindow(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::User_MainWindow)
{
    ui->setupUi(this);

    // 初始显示用户主界面
    this->game = new Gaming(this);
    //this->show();
    this->game->hide();

    // 设置默认界面
    ui->main_tabWidget->setCurrentIndex(0);
    ui->challenger_tabWidget->setCurrentIndex(0);
    ui->questioner_tabWidget->setCurrentIndex(0);

    // 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if (!db.open())
    {
        qDebug() << "Failed to connect database.";
    }

    // 按照已闯关卡数对闯关者降序排序
    sort_challengeer(PASSED_LEVELS, ui->challenger_tableView_1);
    // 按照等级对闯关者降序排序
    sort_challengeer(LEVEL, ui->challenger_tableView_2);
    // 按照出题数目对出题者降序排序
    sort_questioner(QUESTION_COUNT, ui->questioner_tableView_1);
    // 按照等级对出题者降序排序
    sort_questioner(LEVEL, ui->questioner_tableView_2);

    //刷新排行榜
    connect(ui->crank_ref_pushButton, &QPushButton::clicked, this, [ = ]()
    {
        sort_challengeer(PASSED_LEVELS, ui->challenger_tableView_1);
        sort_challengeer(LEVEL, ui->challenger_tableView_2);
    });
    connect(ui->qrank_ref_pushButton, &QPushButton::clicked, this, [ = ]()
    {
        sort_questioner(QUESTION_COUNT, ui->questioner_tableView_1);
        sort_questioner(LEVEL, ui->questioner_tableView_2);
    });

    //查询用户
    connect(ui->search_pushButton, &QPushButton::clicked, this, &User_MainWindow::search);
    ui->search_tableView->horizontalHeader()->setSectionsClickable(false);
    ui->search_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->search_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 用户主界面和游戏界面切换
    connect(this, &User_MainWindow::begin_new_game, this, [ = ]()
    {
        this->hide();
        this->game->show();
    });
    connect(this->game, &Gaming::change_to_user_mainwindow, this, [ = ]()
    {
        this->show();
        this->game->hide();

    });
    connect(this, &User_MainWindow::continue_game, this, [ = ]()
    {

        this->hide();
        this->game->show();
    });
    connect(this->game, &Gaming::change_to_user_mainwindow, this, [ = ]()
    {
        this->show();
        this->game->hide();
    });

}

User_MainWindow::~User_MainWindow()
{
    delete ui;
}

// 对闯关者根据关键字key排序
void User_MainWindow::sort_challengeer(int key, QTableView* tableView)
{
    QSqlTableModel* pModel = new QSqlTableModel(this);

    // 设置表格格式
    pModel->setTable("user");
    pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel->setFilter(QObject::tr("role = %1").arg(CHALLENGER));
    pModel->select();
    pModel->removeColumn(1);
    pModel->removeColumn(1);
    pModel->removeColumn(3);
    pModel->removeColumn(4);
    pModel->removeColumn(4);
    pModel->setHeaderData(0, Qt::Horizontal, "用户名");
    pModel->setHeaderData(1, Qt::Horizontal, "等级");
    pModel->setHeaderData(2, Qt::Horizontal, "经验值");
    pModel->setHeaderData(3, Qt::Horizontal, "已闯关卡数");
    pModel->sort(key, Qt::DescendingOrder);
    tableView->horizontalHeader()->setSectionsClickable(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(pModel);
}

// 对出题者根据关键字key排序
void User_MainWindow::sort_questioner(int key, QTableView* tableView)
{
    QSqlTableModel* pModel = new QSqlTableModel(this);

    // 设置表格格式
    pModel->setTable("user");
    pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel->setFilter(QObject::tr("role = %1").arg(QUESTIONER));
    pModel->select();
    pModel->removeColumn(1);
    pModel->removeColumn(1);
    pModel->removeColumn(4);
    pModel->removeColumn(4);
    pModel->removeColumn(4);
    pModel->setHeaderData(0, Qt::Horizontal, "用户名");
    pModel->setHeaderData(1, Qt::Horizontal, "等级");
    pModel->setHeaderData(2, Qt::Horizontal, "经验值");
    pModel->setHeaderData(3, Qt::Horizontal, "出题数目");
    pModel->sort(key, Qt::DescendingOrder);
    tableView->horizontalHeader()->setSectionsClickable(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(pModel);
}

void User_MainWindow::search()
{
    //用户信息
    QString username = ui->usr_lineEdit->text();
    QString level = ui->level_lineEdit->text();
    QString passed_levels = ui->passedlevels_lineEdit->text();
    QString question_cnt = ui->questioncnt_lineEdit->text();
    int role = ui->role_comboBox->currentIndex();

    QSqlTableModel* pModel = new QSqlTableModel(this);

    //过滤条件
    QString condition = "";
    if(username != "")
        condition += QString("username = '%1'").arg(username);
    if(level != "")
    {
        if(condition != "")
            condition += QString(" and level = %1").arg(level);
        else
            condition += QString("level = %1").arg(level);
    }
    if(passed_levels != "")
    {
        if(condition != "")
            condition += QString(" and passedLevels = %1").arg(passed_levels);
        else
            condition += QString("passedLevels = %1").arg(passed_levels);
    }
    if(question_cnt != "")
    {
        if(condition != "")
            condition += QString(" and questionCount = %1").arg(question_cnt);
        else
            condition += QString("questionCount = %1").arg(question_cnt);
    }
    if(condition != "")
        condition += QString(" and role = %1").arg(role);
    else
        condition += QString("role = %1").arg(role);

    qDebug() << condition;
    //表格格式
    pModel->setTable("user");
    pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel->setFilter(condition);
    pModel->select();
    pModel->removeColumn(1);
    pModel->removeColumn(1);
    pModel->removeColumn(5);
    pModel->removeColumn(5);
    pModel->setHeaderData(0, Qt::Horizontal, "用户名");
    pModel->setHeaderData(1, Qt::Horizontal, "等级");
    pModel->setHeaderData(2, Qt::Horizontal, "经验值");
    pModel->setHeaderData(3, Qt::Horizontal, "出题数目");
    pModel->setHeaderData(4, Qt::Horizontal, "已闯关卡数");

    //显示查找结果
    ui->search_tableView->setModel(pModel);
    qDebug() << pModel->rowCount() << " " << pModel->columnCount();
}

void User_MainWindow::closeEvent(QCloseEvent* event)
{
    // 关闭所有窗口
    emit close_all();
}

void User_MainWindow::statusbar_info(const QString& username, const int& role, const int& level, const int& experience, const int& questionCount, const int& passedLevels)
{
    username_label = new QLabel(QString("用户名：") + username, this);
    level_label = new QLabel(QString("等级：") + QString::number(level), this);
    exp_label = new QLabel(QString("经验值：") + QString::number(experience), this);

    //闯关者
    if(role == 0)
    {
        ui->statusbar->addWidget(username_label);
        role_label = new QLabel("角色：闯关者", this);
        ui->statusbar->addWidget(role_label);
        ui->statusbar->addWidget(level_label);
        ui->statusbar->addWidget(exp_label);
        passedlevels_label = new QLabel(QString("已闯关卡数：") + QString::number(passedLevels), this);
        ui->statusbar->addWidget(passedlevels_label);
    }
    //出题者
    else
    {
        ui->statusbar->addWidget(username_label);
        role_label = new QLabel("角色：出题者", this);
        ui->statusbar->addWidget(role_label);
        ui->statusbar->addWidget(level_label);
        ui->statusbar->addWidget(exp_label);
        questioncnt_label = new QLabel(QString("出题数目：") + QString::number(questionCount), this);
        ui->statusbar->addWidget(questioncnt_label);
    }
}

void User_MainWindow::on_new_game_pushButton_clicked()
{
    game->init(1);
    emit begin_new_game();
}


void User_MainWindow::on_continue_game_pushButton_clicked()
{
    game->init(2);
    emit continue_game();
}

