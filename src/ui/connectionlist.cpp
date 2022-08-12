#include "src/ui/connectionlist.h"
#include "ui_connectionlist.h"
#include "src/config/configmanager.h"

#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QPushButton>
#include <QFont>

#include <src/network/networkhelper.h>

ConnectionList::ConnectionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionList)
{
    ui->setupUi(this);
    this->widgetNew = new ConnectionForm(0, ConnectionForm::STATUS_NEW);
    SetConnectedIndex(-1);
    this->SystemProxyManager = new class SystemProxyManager();
    int col = 0;
    this->nameIndex = col++;
    this->serverIndex = col++;
    this->statusIndex = col++;
    this->lastDelayTimeIndex = col++;
    this->usedIndex = col++;
    this->usedHistoryIndex = col++;
    this->lastUseTimeIndex = col++;
    this->TrojanGoManger = new class TrojanGoManger(ConfigManager::GetClientConfigPath());
    this->SetConnectedIndex(-1);

    this->RefleshConnectionList();

    connect(this->widgetNew->findChild<QPushButton*>("ok"),
            &QPushButton::pressed,
            this,
            [=] () {

            QConfigJsonObject::QConnectionConfigJsonObject obj = this->widgetNew->GetFormSettings();
            // 新建操作
            if (this->widgetNew->GetFormStatus() == ConnectionForm::STATUS_NEW) {
                ConfigManager::AddConnectionConfig(obj);
                this->UpdateConnectionList();
            }

            // 编辑操作
            if (this->widgetNew->GetFormStatus() == ConnectionForm::STATUS_EDIT) {
                ConfigManager::EditConnectionConfig(this->widgetNew->GetItemIndex(), obj);
                this->UpdateConnectionList();
            }
            this->widgetNew->hide();
    });

    connect(ui->ConnectionListTable, &QTableWidget::itemSelectionChanged, this, [=] () {
        emit this->connectionUpdated();
    });

    connect(ui->ConnectionListTable, &QTableWidget::cellDoubleClicked, this, [=] (int row) {
        if (this->getConnectedIndex() == row) {
            emit this->requestDisconnect();
        }else{
            emit this->requestConnect();
        }
    });



}

ConnectionList::~ConnectionList()
{
    delete ui;
}

void ConnectionList::setItem(int row, int column, QTableWidgetItem *item)
{
    ui->ConnectionListTable->setItem(row, column, item);
}

void ConnectionList::setHeaders(QStringList list)
{
    ui->ConnectionListTable->setHorizontalHeaderLabels(list);
}

int ConnectionList::RefleshConnectionList()
{
    QConfigJsonObject::QConnectionConfigListJsonObject array = ConfigManager::GetConnectionConfigList();
    // 清空所有item 从文件读取
    this->ClearRows();
    for (int i=0 ; i< array.size(); i++) {
        QConfigJsonObject::QConnectionConfigJsonObject item = array.At(i);
        QString name = item.GetName();
        QString server = item.GetServerAddr();
        int lastDelayTime = item.GetLastDelay();
        int lastUseTime = item.GetLastUseTime();
        QString status = this->getConnectedIndexText(i);

        this->AddConnection(name, server, status, lastDelayTime, 0,0, lastUseTime);
    }

    return 0;
}


int ConnectionList::AddConnection(QString name, QString server, QString status, int lastDelayTime, int used, int usedHistory, int lastUseTime)
{
    int i = this->getRowCount();
    // 添加一个item并且渲染
    this->ui->ConnectionListTable->setRowCount(i+1);
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *serverItem = new QTableWidgetItem(server);
    QTableWidgetItem *statusItem = new QTableWidgetItem(status);
    QTableWidgetItem *lastDelayTimeItem = new QTableWidgetItem(lastDelayTime);
    QTableWidgetItem *usedItem = new QTableWidgetItem(used);
    QTableWidgetItem *usedHistoryItem = new QTableWidgetItem(usedHistory);
    QTableWidgetItem *lastUseTimeItem = new QTableWidgetItem(lastUseTime);

    if (i == getConnectedIndex()){
        QFont *font = new QFont();
        font->setBold(true);
        nameItem->setFont(*font);
        serverItem->setFont(*font);
        statusItem->setFont(*font);
        lastDelayTimeItem->setFont(*font);
        usedItem->setFont(*font);
        usedHistoryItem->setFont(*font);
        lastUseTimeItem->setFont(*font);

        QBrush ConnectedColor(Qt::green);
        statusItem->setForeground(ConnectedColor);

    }else{
        QBrush DisconnectedColor(Qt::gray);
        statusItem->setForeground(DisconnectedColor);
    }

    QBrush lastDelayTimeColor(Qt::green);

    if (lastDelayTime > 0) {
        lastDelayTimeColor.setColor(Qt::green);
        lastDelayTimeItem->setText(QString::number(lastDelayTime) + " ms");
    }else{
        lastDelayTimeColor.setColor(Qt::red);
        lastDelayTimeItem->setText("未知");
    }
    lastDelayTimeItem->setForeground(lastDelayTimeColor);

    this->setItem(i, nameIndex, nameItem);
    this->setItem(i, serverIndex, serverItem);
    this->setItem(i, statusIndex, statusItem);
    this->setItem(i, lastDelayTimeIndex, lastDelayTimeItem);
    this->setItem(i, usedIndex, usedItem);
    this->setItem(i, usedHistoryIndex, usedHistoryItem);
    this->setItem(i, lastUseTimeIndex, lastUseTimeItem);
    return 0;
}

int ConnectionList::getRowCount()
{
    return ui->ConnectionListTable->rowCount();
}

void ConnectionList::ClearRows()
{
    ui->ConnectionListTable->clearContents();
    ui->ConnectionListTable->setRowCount(0);
}

int ConnectionList::Connect()
{
    int index = this->GetSelectedRowNum();
    return this->ConnectTo(index);
}

int ConnectionList::ConnectTo(int index)
{
    if (index == -1) {
        index = ConfigManager::GetConfigs().GetLastConnectItem();
    }
    if (index == -1) {
        index = 0;
    }
    ConfigManager::CreateClientConfigByItemIndex(index);
    this->TrojanGoManger->start();
    this->SetConnectedIndex(index);
    RefleshConnectionList();
    emit this->connectionUpdated();
    ui->ConnectionListTable->setCurrentCell(index, 0);
    this->SystemProxyManager->SetProxy(ConfigManager::GetConfigs().GetLocalAddr(), ConfigManager::GetConfigs().GetLocalPort());
    this->SetLastConnectedIndex(index);
    return index;
}

int ConnectionList::ReConnect()
{
    int index = this->getConnectedIndex();
    this->DisConnect();
    return this->ConnectTo(index);
}

QConfigJsonObject::QConnectionConfigJsonObject ConnectionList::GetConnectedItem() {
    return ConfigManager::GetConnectionConfigItem(this->connnectedRowIndex);
}

int ConnectionList::DisConnect()
{
    int index = this->getConnectedIndex();
    if (index > -1) {
        SetConnectedIndex(-1);
        this->TrojanGoManger->Disconnet();
        RefleshConnectionList();
    }
    this->SystemProxyManager->ReSetProxy();
    ui->ConnectionListTable->setCurrentCell(index, 0);
    emit this->connectionUpdated();
    return index;
}

int ConnectionList::getConnectedIndex()
{
    return this->connnectedRowIndex;
}

void ConnectionList::SetConnectedIndex(int index)
{
    this->connnectedRowIndex = index;
}

int ConnectionList::GetSelectedRowNum()
{
    // 设置了只能选中一行
    QList items = ui->ConnectionListTable->selectedItems();
    if (items.length() > 0) {
        return ui->ConnectionListTable->row(items.at(0));
    }

    return -1;
}


QConfigJsonObject::QConnectionConfigJsonObject ConnectionList::GetSelectedRowItem()
{
    return ConfigManager::GetConnectionConfigItem(GetSelectedRowNum());
}

void ConnectionList::DelSelectedRow()
{
    if (this->getRowCount() == 0) {
        return;
    }
    int rowNum = this->GetSelectedRowNum();
    if (rowNum == -1) {
        return;
    }
    ConfigManager::DelConnectionConfig(rowNum);
    this->UpdateConnectionList();
}


void ConnectionList::UpSelectedRow()
{
    if (this->getRowCount() == 0) {
        return;
    }
    int rowNum = this->GetSelectedRowNum();
    if (rowNum == -1) {
        return;
    }
    ConfigManager::UpConnectionConfig(rowNum);
    this->UpdateConnectionList();
    ConfigManager::UpConnectionConfig(rowNum);
}

void ConnectionList::DownSelectedRow()
{
    if (this->getRowCount() == 0) {
        return;
    }
    int rowNum = this->GetSelectedRowNum();
    if (rowNum == -1) {
        return;
    }
    ConfigManager::DownConnectionConfig(rowNum);
    this->UpdateConnectionList();
    ConfigManager::DownConnectionConfig(rowNum);
}


void ConnectionList::SetWidgetSelectedLine()
{
    int rowNum = this->GetSelectedRowNum();
    if (rowNum == -1) {
        return;
    }

    QConfigJsonObject::QConnectionConfigJsonObject obj = ConfigManager::GetConnectionConfigItem(rowNum);
    this->widgetNew->SetItemIndex(rowNum);
    this->widgetNew->SetSettings(&obj);
}

QString ConnectionList::getConnectedIndexText(int nowIndex)
{
    if (getConnectedIndex() == nowIndex) {
        return "Connected";
    }else{
        return "Disconnected";
    }
}

void ConnectionList::UpdateConnectionList(){
    this->RefleshConnectionList();
}

void ConnectionList::SetDelayTested(int index, int delaytime)
{
    ConfigManager::SetLastDelayTime(index, delaytime);
    this->UpdateConnectionList();
}

void ConnectionList::SetLastConnectedIndex(int index)
{
    ConfigManager::SetLastConnectedIndex(index);
}



