#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QWidget>
#include <QFile>
#include "src/config/qconfigjsonobject.h"
#include "src/ui/connectionform.h"

class ConfigManager : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigManager(QWidget *parent = nullptr);
    int UpConnectionConfig(int index);

    int DelConnectionConfig(int index);
    QConfigJsonObject GetConfigs();
    QString getAbsolutePath(QString str);
    void SaveConfig(QConfigJsonObject config);
    void CreateClientConfigByItemIndex(int index);
    int EditConnectionConfig(int Index, QConfigJsonObject::QConnectionConfigJsonObject obj);
    int AddConnectionConfig(QConfigJsonObject::QConnectionConfigJsonObject obj);
    QConfigJsonObject::QConnectionConfigListJsonObject GetConnectionConfigList();
    QConfigJsonObject::QConnectionConfigJsonObject GetConnectionConfigItem(int index);
    QString GetClientConfigPath();
private:
    QString connectionPath;
    QString clientConfigPath;

signals:
    // 当配置文件发生改变的时候触发该信号
    void configFileUpdated();
};

#endif // CONFIGMANAGER_H
