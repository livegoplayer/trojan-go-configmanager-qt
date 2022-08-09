#include "src/ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/trojan/trojangomanger.h"
#include "src/traymenu/traymenu.h"

#include <QNetwork.h>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showAction = new QAction("显示", this);
    this->minAction = new QAction("最小化", this);
    this->maxAction = new QAction("最大化", this);

    this->advancedSettingsForm = new AdvancedSettingsForm();
    this->QThemeConfig = new class QThemeConfig();
    this->QThemeConfig->updateTheme();

    ui->ActionConnect->installEventFilter(this);
    ui->ActionDisconnect->installEventFilter(this);
    ui->ActionTestDelay->installEventFilter(this);
    ui->ActionEdit->installEventFilter(this);
    ui->ActionDel->installEventFilter(this);
    ui->ActionShare->installEventFilter(this);
    ui->ActionUp->installEventFilter(this);
    ui->ActionDown->installEventFilter(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    connect(ui->ActionAdd,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->widgetNew->SetFormStatus(0);
            ui->CL->widgetNew->show();
    });

    connect(ui->ActionEdit,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->widgetNew->SetFormStatus(1);
            int rowNum = ui->CL->GetSelectedRowNum();
            if (rowNum == -1) {
                return;
            }

            ui->CL->SetWidgetSelectedLine();
            ui->CL->widgetNew->show();
    });

    connect(ui->ActionDel,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->DelSelectedRow();
    });

    connect(ui->ActionUp,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->UpSelectedRow();
    });


    connect(ui->ActionAdditionalSettings,
            &QAction::triggered,
            this,
            [=] () {
            this->advancedSettingsForm->InitAdvancedSettingFoem();
            this->advancedSettingsForm->show();
    });

    connect(ui->ActionConnect,
            &QAction::triggered,
            this,
            [=] () {
            this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_on"));
            int index = ui->CL->Connect();
            QString name = ui->CL->ConfigManager->GetConnectionConfigItem(index).GetName();
            this->QSystemTrayIcon->showMessage("conneted", name + "已连接");
    });

    connect(ui->ActionDisconnect,
            &QAction::triggered,
            this,
            [=] () {
            this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_off"));
            int index = ui->CL->DisConnect();
            if (index > -1)  {
                QString name = ui->CL->ConfigManager->GetConnectionConfigItem(index).GetName();
                this->QSystemTrayIcon->showMessage("disconneted", name + "已断开");
            }else{
                this->QSystemTrayIcon->showMessage("错误", "没有活动连接");
            }
    });

    connect(this->showAction,
            &QAction::triggered,
            this,
            [=] () {
            showNormal();
            raise();
            activateWindow();
    });

    connect(this->minAction,
            &QAction::triggered,
            this,
            [=] () {
            this->hide();
    });

    connect(this->maxAction,
            &QAction::triggered,
            this,
            [=] () {
            this->showMaximized();
    });

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        this->QSystemTrayIcon = new class QSystemTrayIcon(this);
        TrayMenu *pTrayMenu = new TrayMenu(this);
        pTrayMenu->addAction(this->showAction);
        pTrayMenu->addAction(this->minAction);
        pTrayMenu->addSeparator();
        pTrayMenu->addAction(ui->ActionConnect);
        pTrayMenu->addAction(ui->ActionDisconnect);
        pTrayMenu->addSeparator();
        pTrayMenu->addAction(ui->ActionQuit);
        this->QSystemTrayIcon->setContextMenu(pTrayMenu);

        this->QSystemTrayIcon->setToolTip(QString::fromLocal8Bit("trojan-go-configmanager"));
        this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_off"));

        this->QSystemTrayIcon->show();
        connect(this->QSystemTrayIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitQuitAction(QApplication *a) {
    connect(ui->ActionQuit,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->DisConnect();
            a->quit();
    });
}

// 激活系统托盘
void MainWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    // 单击托盘显示窗口
    case QSystemTrayIcon::Trigger:
    {
        break;
    }
    // 双击
    case QSystemTrayIcon::DoubleClick:
    {
        showNormal();
        raise();
        activateWindow();
        break;
    }
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int closeApp = QMessageBox::question(this, "Note", "你想要最小化到托盘吗?");
    if(closeApp == QMessageBox::Yes)
    {
        this->hide();
        event->ignore();
    }
    else
    {
        ui->CL->DisConnect();
        event->accept();  //关闭
    }
}



