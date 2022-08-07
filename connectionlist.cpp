#include "connectionlist.h"
#include "ui_connectionlist.h"
#include "configmanager.h"

#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QPushButton>

ConnectionList::ConnectionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionList)
{
    ui->setupUi(this);
    this->ConfigManager = new class ConfigManager();
    this->widgetNew = new ConnectionForm(0, ConnectionForm::STATUS_NEW);
    this->connnectedRowIndex = -1;
    int col = 0;
    this->nameIndex = col++;
    this->serverIndex = col++;
    this->statusIndex = col++;
    this->lastDelayTimeIndex = col++;
    this->usedIndex = col++;
    this->usedHistoryIndex = col++;
    this->lastUseTimeIndex = col++;


    this->RefleshConnectionList();

    connect(this->ConfigManager, &ConfigManager::configFileUpdated, this, &ConnectionList::UpdateConnectionList);

    connect(this->widgetNew->findChild<QPushButton*>("ok"),
            &QPushButton::pressed,
            this,
            [=] () {

            QConfigJsonObject::QConnectionConfigJsonObject obj = this->widgetNew->GetFormSettings();
            // 新建操作
            if (this->widgetNew->GetFormStatus() == ConnectionForm::STATUS_NEW) {
                this->ConfigManager->AddConnectionConfig(obj);
            }

            // 编辑操作
            if (this->widgetNew->GetFormStatus() == ConnectionForm::STATUS_EDIT) {
                this->ConfigManager->EditConnectionConfig(this->widgetNew->GetItemIndex(), obj);
            }
            this->widgetNew->hide();
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
    QConfigJsonObject::QConnectionConfigListJsonObject array = this->ConfigManager->GetConnectionConfigList();
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

void ConnectionList::RefleshItem(int row, int col, QString val)
{
    this->setItem(row, col, new QTableWidgetItem(val));
}

int ConnectionList::AddConnection(QString name, QString server, QString status, int lastDelayTime, int used, int usedHistory, int lastUseTime)
{
    int i = this->getRowCount();
    // 添加一个item并且渲染
    this->ui->ConnectionListTable->setRowCount(i+1);
    this->setItem(i, nameIndex, new QTableWidgetItem(name));
    this->setItem(i, serverIndex, new QTableWidgetItem(server));
    this->setItem(i, statusIndex, new QTableWidgetItem(status));
    this->setItem(i, lastDelayTimeIndex, new QTableWidgetItem(lastDelayTime));
    this->setItem(i, usedIndex, new QTableWidgetItem(used));
    this->setItem(i, usedHistoryIndex, new QTableWidgetItem(usedHistory));
    this->setItem(i, lastUseTimeIndex, new QTableWidgetItem(lastUseTime));
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

void ConnectionList::Connect(int index)
{
    this->connnectedRowIndex = index;
    return this->RefleshItem(index, this->statusIndex, this->getConnectedIndexText(index));
}

void ConnectionList::DisConnect(int index)
{
    this->connnectedRowIndex = -1;
    return this->RefleshItem(index, this->statusIndex, this->getConnectedIndexText(index));
}

int ConnectionList::getConnectedIndex()
{
    return this->connnectedRowIndex;
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

void ConnectionList::DelSelectedRow()
{
    if (this->getRowCount() == 0) {
        return;
    }
    int rowNum = this->GetSelectedRowNum();
    if (rowNum == -1) {
        return;
    }
    this->ConfigManager->DelConnectionConfig(rowNum);
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
    this->ConfigManager->UpConnectionConfig(rowNum);
}

void ConnectionList::SetWidgetSelectedLine()
{
    int rowNum = this->GetSelectedRowNum();
    if (rowNum == -1) {
        return;
    }

    QConfigJsonObject::QConnectionConfigJsonObject obj = this->ConfigManager->GetConnectionConfigItem(rowNum);
    this->widgetNew->SetItemIndex(rowNum);
    this->widgetNew->SetSettings(&obj);
}

QString ConnectionList::getConnectedIndexText(int nowIndex)
{
    if (this->connnectedRowIndex ==  nowIndex) {
        return "connected";
    }else{
        return "disconnected";
    }
}

void ConnectionList::UpdateConnectionList(){
    this->RefleshConnectionList();
}


