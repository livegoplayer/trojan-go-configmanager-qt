#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QWidget>
#include <QFile>
#include "src/config/qconfigjsonobject.h"
#include "src/ui/connectionform.h"

class ConfigManager
{
public:
    explicit ConfigManager();
    static int DownConnectionConfig(int index);
    static int UpConnectionConfig(int index);
    static int DelConnectionConfig(int index);
    static int EditConnectionConfig(int Index, QConfigJsonObject::QConnectionConfigJsonObject obj);
    static void CreateClientConfigByItemIndex(int index);
    static int AddConnectionConfig(QConfigJsonObject::QConnectionConfigJsonObject obj);
    static QConfigJsonObject GetConfigs();

    static QString getAbsolutePath(QString str);
    static void SaveConfig(QConfigJsonObject config);
    static QConfigJsonObject::QConnectionConfigListJsonObject GetConnectionConfigList();
    static QConfigJsonObject::QConnectionConfigJsonObject GetConnectionConfigItem(int index);
    static void SetHideClose(bool value);
    static bool GetHideClose();
    static QString GetConnectionPath();
    static QString GetClientConfigPath();

    static int SetLastDelayTime(int Index, int lastDelayTime);
    static void openLogFileDialog();
    static int SetLastConnectedIndex(int Index);
    static bool GetAutoConnect();
    static void SetAutoConnect(bool value);
    static QString getShareLinkConfigPath();
    static void addConnectionFromShareLink(QString shareLink);
private:
    constexpr static const char connectionPath[] = "config/connectionList.json";
    constexpr static const char clientConfigPath[] = "config/config.json";
    constexpr static const char ShareLinkConfigPath[] = "config/share_link_config.json";

};

#endif // CONFIGMANAGER_H
