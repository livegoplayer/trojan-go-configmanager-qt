#include "src/ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/trojan/trojangomanger.h"
#include "src/traymenu/traymenu.h"

#include <QNetwork.h>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QClipboard>
#include <QMessageBox>

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
    this->updateTheme();
    this->updateHideClose();
    this->updateAutoConnect();
    this->reflashActions(-1);

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

    connect(ui->ActionDown,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->DownSelectedRow();
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
            this->onConnect();
    });

    connect(ui->ActionDisconnect,
            &QAction::triggered,
            this,
            [=] () {
            this->onDisconnect();
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

    connect(ui->actionlight,
            &QAction::triggered,
            this,
            [=] () {
            this->QThemeConfig->SetLightTheme();
            this->updateTheme();
    });

    connect(ui->actiondark,
            &QAction::triggered,
            this,
            [=] () {
            this->QThemeConfig->SetDrakTheme();
            this->updateTheme();
    });

    connect(ui->actionHideClose,
            &QAction::triggered,
            this,
            [=] (bool checked) {
            ConfigManager::SetHideClose(checked);
            this->updateHideClose();
    });

    connect(ui->actionAutoConnect,
            &QAction::triggered,
            this,
            [=] (bool checked) {
            ConfigManager::SetAutoConnect(checked);
            this->updateAutoConnect();
    });

    connect(ui->ActionTestDelay,
            &QAction::triggered,
            this,
            &MainWindow::onTestDelay)
    ;

    connect(ui->ActionTrojanLog,
            &QAction::triggered,
            this,
            [=] () {
            ConfigManager::openLogFileDialog();
    });

    connect(ui->CL, &ConnectionList::connectionUpdated, this, &MainWindow::onConnetChange);

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        this->QSystemTrayIcon = new class QSystemTrayIcon(this);
        TrayMenu *pTrayMenu = new TrayMenu(this);
        pTrayMenu->addAction(this->showAction);
        pTrayMenu->addAction(this->minAction);
        pTrayMenu->addSeparator();
        pTrayMenu->addAction(ui->ActionQuit);
        this->QSystemTrayIcon->setContextMenu(pTrayMenu);

        this->QSystemTrayIcon->setToolTip(QString::fromLocal8Bit("trojan-go-configmanager"));
        this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_off"));

        this->QSystemTrayIcon->show();
        connect(this->QSystemTrayIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
    }

    connect(ui->CL, &ConnectionList::requestConnect, this, &MainWindow::onConnect);
    connect(ui->CL, &ConnectionList::requestDisconnect, this, &MainWindow::onDisconnect);

    connect(ui->ActionQuit,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->DisConnect();
            QApplication::quit();
    });

    connect(this->advancedSettingsForm,
            &AdvancedSettingsForm::requestReconnect,
            this,
            &MainWindow::onReconnect);

    connect(ui->ActionImportFromClipboard,
            &QAction::triggered,
            this,
            [=] () {
        QClipboard *br = QApplication::clipboard();
        QString original =   br->text();
        if (original.startsWith("trojan")) {
            if (!original.startsWith("trojan-go")) {
                original.replace("trojan://", "trojan-go://");
            }
            ConfigManager::addConnectionFromShareLink(original);
            ui->CL->RefleshConnectionList();
        }else{
           QMessageBox::warning(this, "提示", "不是有效的分享链接");
        }
    });

    this->CheckAutoConnect();

}

MainWindow::~MainWindow()
{
    delete ui;
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
    bool hideClose = ConfigManager::GetHideClose();
    if(hideClose)
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

void MainWindow::CheckAutoConnect()
{
    if (ConfigManager::GetAutoConnect()) {
        this->onConnect();
    }
}



void MainWindow::updateTheme()
{
    this->QThemeConfig->updateTheme();
    this->updateThemeAction();
}

void MainWindow::updateHideClose()
{
    bool HideClose = ConfigManager::GetHideClose();
    ui->actionHideClose->setChecked(HideClose);
}


void MainWindow::updateAutoConnect()
{
    bool value = ConfigManager::GetAutoConnect();
    ui->actionAutoConnect->setChecked(value);
}


void MainWindow::updateThemeAction() {
    if (this->QThemeConfig->isDarkTheme()){
        ui->actiondark->setChecked(true);
        ui->actionlight->setChecked(false);
    }else{
        ui->actiondark->setChecked(false);
        ui->actionlight->setChecked(true);
    }
}

void MainWindow::onConnetChange(){
    this->reflashActions(ui->CL->GetSelectedRowNum());
}

void MainWindow::onDisconnect(){
    this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_off"));
    int index = ui->CL->DisConnect();
    if (index > -1)  {
        QString name = ConfigManager::GetConnectionConfigItem(index).GetName();
        this->QSystemTrayIcon->showMessage("disconneted", name + "已断开");
    }else{
        this->QSystemTrayIcon->showMessage("错误", "没有活动连接");
    }
}

void MainWindow::onConnect(){
    if (!ConfigManager::GetConnectionConfigList().isEmpty()) {

        this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_on"));
        int index = ui->CL->Connect();
        QString name = ConfigManager::GetConnectionConfigItem(index).GetName();
        this->QSystemTrayIcon->showMessage("conneted", name + "已连接");
    }else{
        this->QSystemTrayIcon->showMessage("错误", "请先添加配置");
    }
}

void MainWindow::onTestDelay(){
    int rowNum = ui->CL->GetSelectedRowNum();
    if (rowNum == -1) { // 测试所有的延迟
//        for (int i = 0; i< ui->CL->getRowCount(); i++){
//            int delay = NetworkHelper::Ping(ConfigManager::GetConnectionConfigItem(i).GetName());
//            ui->CL->SetDelayTested(i, delay);
//        }
        return;
    }
    int delay = NetworkHelper::Ping(ConfigManager::GetConnectionConfigItem(rowNum).GetServerAddr());
    ui->CL->SetDelayTested(rowNum, delay);
}

void MainWindow::onReconnect(){
    if (!ConfigManager::GetConnectionConfigList().isEmpty()) {
        this->QSystemTrayIcon->setIcon(QIcon(":/icons/trojan_on"));
        int index = ui->CL->ReConnect();
        QString name = ConfigManager::GetConnectionConfigItem(index).GetName();
        this->QSystemTrayIcon->showMessage("conneted", name + "重新连接成功");
    }else{
        this->QSystemTrayIcon->showMessage("错误", "请先添加配置");
    }
}

void MainWindow::reflashActions(int row){
    if (row == -1) {
        ui->ActionTestDelay->setDisabled(true);
        ui->ActionEdit->setDisabled(true);
        ui->ActionDel->setDisabled(true);
        ui->ActionShare->setDisabled(true);
        ui->ActionUp->setDisabled(true);
        ui->ActionDown->setDisabled(true);
        ui->ActionConnect->setDisabled(true);
        ui->ActionDisconnect->setDisabled(true);
        return;
    }

    ui->ActionTestDelay->setEnabled(true);
    ui->ActionEdit->setEnabled(true);
    ui->ActionDel->setEnabled(true);
    ui->ActionShare->setEnabled(true);

    if (row > 0) {
        ui->ActionUp->setEnabled(true);
    }else{
        ui->ActionUp->setDisabled(true);
    }

    if (row < ui->CL->getRowCount() - 1) {
        ui->ActionDown->setEnabled(true);
    }else{
        ui->ActionDown->setDisabled(true);
    }

    if (row == ui->CL->getConnectedIndex()){
        ui->ActionConnect->setDisabled(true);
        ui->ActionDisconnect->setEnabled(true);
    }else{
        ui->ActionConnect->setEnabled(true);
        ui->ActionDisconnect->setDisabled(true);
    }
}

