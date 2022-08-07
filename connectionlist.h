#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

#include "configmanager.h"

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class ConnectionList;
}

class ConnectionList : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionList(QWidget *parent = nullptr);
    ~ConnectionList();

    int RefleshConnectionList();
    void RefleshItem(int row, int col, QString val);


    void ClearRows();

    // 配置管理组件
    ConfigManager *ConfigManager;

//    // 配置编辑组件
    ConnectionForm *widgetNew;

    int GetSelectedRowNum();

    void UpSelectedRow();

    void DelSelectedRow();
    void SetWidgetSelectedLine();

    int AddConnection(QString name, QString server, QString status, int lastDelayTime, int used, int usedHistory, int lastUseTime);
private:
    Ui::ConnectionList *ui;

    int getConnectedIndex(int index);

    void DisConnect(int index);

    void Connect(int index);

    int getRowCount();

    void setItem(int row, int column, QTableWidgetItem *item);

    int connnectedRowIndex;

    int nameIndex;
    int serverIndex;
    int statusIndex;
    int lastDelayTimeIndex;
    int usedIndex;
    int usedHistoryIndex;
    int lastUseTimeIndex;

    int getConnectedIndex();

    QString getConnectedIndexText(int nowIndex);

    void setHeaders(QStringList list);

public slots:

    void UpdateConnectionList();
};



#endif // CONNECTIONLIST_H
