#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

#include "src/config/configmanager.h"
#include "src/proxy/systemproxymanager.h"
#include "src/trojan/trojangomanger.h"

#include <QWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView>

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

    void ClearRows();


//    // 配置编辑组件
    ConnectionForm *widgetNew;

    // trojan-go
    TrojanGoManger *TrojanGoManger;

    // 系统代理设置
    SystemProxyManager *SystemProxyManager;

    int GetSelectedRowNum();

    void UpSelectedRow();

    void DelSelectedRow();
    void SetWidgetSelectedLine();

    int AddConnection(QString name, QString server, QString status, int lastDelayTime, int used, int usedHistory, int lastUseTime);
    QConfigJsonObject::QConnectionConfigJsonObject GetConnectedItem();
    int DisConnect();
    int Connect();
    void DownSelectedRow();
    void SetConnectedIndex(int index);
    int getConnectedIndex();
    int getRowCount();

    QConfigJsonObject::QConnectionConfigJsonObject GetSelectedRowItem();
    void SetDelayTested(int index, int delaytime);
    int ReConnect();
    void SetLastConnectedIndex(int index);
    int ConnectTo(int index);
private:
    Ui::ConnectionList *ui;


    void setItem(int row, int column, QTableWidgetItem *item);

    int connnectedRowIndex;

    int nameIndex;
    int serverIndex;
    int statusIndex;
    int lastDelayTimeIndex;
    int usedIndex;
    int usedHistoryIndex;
    int lastUseTimeIndex;

    QString getConnectedIndexText(int nowIndex);

    void setHeaders(QStringList list);
    void UpdateConnectionList();



signals:
    void connectionUpdated();
    void requestConnect();
    void requestDisconnect();
};



#endif // CONNECTIONLIST_H
