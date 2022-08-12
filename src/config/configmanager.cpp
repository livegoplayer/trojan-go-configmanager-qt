#include "src/config/configmanager.h"
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QFile>
#include "src/config/qconfigjsonobject.h"
#include "src/config/qtrojangoclientconfigjsonobject.h"
#include "src/trojan/trojangomanger.h"
#include <QDesktopServices>

// 配置管理类
ConfigManager::ConfigManager()
{
}

QString ConfigManager::getAbsolutePath(QString str)
{
    QString sAppPath = QCoreApplication::applicationDirPath();
    QString sFilePath = sAppPath+"/"+str;
    return sFilePath;
}

QString ConfigManager::GetConnectionPath()
{
    return getAbsolutePath(connectionPath);
}

QString ConfigManager::getShareLinkConfigPath()
{
    return getAbsolutePath(ShareLinkConfigPath);
}

QString ConfigManager::GetClientConfigPath()
{
    return getAbsolutePath(clientConfigPath);
}


int ConfigManager::AddConnectionConfig(QConfigJsonObject::QConnectionConfigJsonObject obj)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());
    qConfigJsonObject.AddConnectionConfig(obj);
    SaveConfig(qConfigJsonObject);
    return 0;
}

int ConfigManager::SetLastDelayTime(int Index, int lastDelayTime)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());
    qConfigJsonObject.SetLastDelayTime(Index, lastDelayTime);
    SaveConfig(qConfigJsonObject);
    return 0;
}

int ConfigManager::SetLastConnectedIndex(int Index)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());
    qConfigJsonObject.SetLastConnectItem(Index);
    SaveConfig(qConfigJsonObject);
    return 0;
}

int ConfigManager::EditConnectionConfig(int Index, QConfigJsonObject::QConnectionConfigJsonObject obj)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());
    qConfigJsonObject.EditConnectionConfig(Index, obj);
    SaveConfig(qConfigJsonObject);
    return 0;
}

int ConfigManager::DelConnectionConfig(int index)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());

    qConfigJsonObject.DelConnectionConfig(index);
    SaveConfig(qConfigJsonObject);
    return 0;
}


int ConfigManager::UpConnectionConfig(int index)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());

    qConfigJsonObject.UpConnectionConfig(index);
    SaveConfig(qConfigJsonObject);

    return 0;
}

int ConfigManager::DownConnectionConfig(int index)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());

    qConfigJsonObject.DownConnectionConfig(index);
    SaveConfig(qConfigJsonObject);
    return 0;
}



QConfigJsonObject ConfigManager::GetConfigs()
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());
    return qConfigJsonObject;
}

void ConfigManager::SaveConfig(QConfigJsonObject config)
{
    config.SaveToFile(GetConnectionPath());
}


QConfigJsonObject::QConnectionConfigListJsonObject ConfigManager::GetConnectionConfigList()
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(GetConnectionPath());
    return qConfigJsonObject.GetConnectionList();
}

QConfigJsonObject::QConnectionConfigJsonObject ConfigManager::GetConnectionConfigItem(int index)
{
    return GetConnectionConfigList().At(index);
}

void ConfigManager::SetHideClose(bool value)
{
    QConfigJsonObject config = *GetConfigs().SetHideClose(value);
    SaveConfig(config);
}

bool ConfigManager::GetHideClose()
{
    return GetConfigs().GetHideClose();
}

bool ConfigManager::GetAutoConnect()
 {
     return GetConfigs().GetAutoConnect();
 }

void ConfigManager::SetAutoConnect(bool value)
{
    QConfigJsonObject config = *GetConfigs().SetAutoConnect(value);
    SaveConfig(config);
}

void ConfigManager::CreateClientConfigByItemIndex(int index)
{
    QConfigJsonObject config = GetConfigs();
    QConfigJsonObject::QConnectionConfigListJsonObject array = config.GetConnectionList();
    QConfigJsonObject::QConnectionConfigJsonObject configItem = array.At(index);
    QString server = configItem.GetServerAddr();
    int port = configItem.GetServerPort();
    QString passwpord = configItem.GetPassword();

    QJsonArray *passwordList = new QJsonArray();
    passwordList->append(passwpord);

    QTrojanGoClientConfigJsonObject obj = QTrojanGoClientConfigJsonObject::GetDefaulObj();
    obj.SetLocalAddr(config.GetLocalAddr())->
            SetLocalPort(config.GetLocalPort())->
            SetRemoteAddr(server)->
            SetRemotePort(port)->
            SetLogLevel(config.GetLogLevel())->
            SetLogFilePath(config.GetLogFilePath())->
            SetPasswordList(*passwordList)->
            SetDisableHttpCheckKey(config.GetDisableHttpCheckKey())->
            SetUDPTimeoutKey(config.GetUDPTimeoutKey())->
            SetMuxConfigEnabled(config.GetMuxConfigEnabled())->
            SetMuxConfigConcurrency(config.GetMuxConfigConcurrency())->
            SetMuxConfigIdleTimeout(config.GetMuxConfigIdleTimeout())->
            SetTCPConfigNoDelay(config.GetTCPConfigNoDelay())->
            SetTCPConfigKeepAlive(config.GetTCPConfigKeepAlive())->
            SetTCPPreferIpv4(config.GetTCPConfigPreferIpv4())->
            SetRouterConfigEnabled(config.GetRouterConfigEnabled())->
            SetSSLConfigVerify(configItem.GetSSLConfigVerify())->
            SetSSLConfigVerifyHostname(configItem.GetSSLConfigVerifyHostname())->
            SetSSLConfigCert(configItem.GetSSLConfigCert())->
            SetSSLConfigKey(configItem.GetSSLConfigKey())->
            SetSSLConfigKeyPassword(configItem.GetSSLConfigKeyPassword())->
            SetSSLConfigCipher(configItem.GetSSLConfigCipher())->
            SetSSLConfigCurves(configItem.GetSSLConfigCurves())->
            SetSSLConfigPreferServerCipher(configItem.GetSSLConfigPreferServerCipher())->
            SetSSLConfigSni(configItem.GetSSLConfigSni())->
            SetSSLConfigAlpn(configItem.GetSSLConfigAlpn())->
            SetSSLConfigSessionTicket(configItem.GetSSLConfigSessionTicket())->
            SetSSLConfigReuseSession(configItem.GetSSLConfigReuseSession())->
            SetSSLConfigPlainHttpResponse(configItem.GetSSLPlainHttpResponse())->
            SetSSLConfigFallbackAddr(configItem.GetSSLFallbackAddr())->
            SetSSLConfigFallbackPort(configItem.GetSSLFallbackPort())->
            SetSSLConfigFingerprint(configItem.GetSSLConfigFingerprint());

    if (obj.GetRouterConfigEnabled()) {
        if (config.GetRouterConfigByPsssEnabled()) {
            obj.SetRouterConfigByPsssList(config.GetRouterConfigByPsssList());
        }

        if (config.GetRouterConfigProxyEnabled()){
            obj.SetRouterConfigProxyList(config.GetRouterConfigProxyList());
        }

        if (config.GetRouterConfigBlockEnabled()) {
            obj.SetRouterConfigBlockList(config.GetRouterConfigBlockList());
        }

        obj.SetRouterConfigDefaultPolicy(config.GetRouterConfigDefaultPolicy())->
                SetRouterConfigDomainStrategy(config.GetRouterConfigDomainStrategy())->
                SetRouterConfigGeoip(config.GetRouterConfigGeoip())->
                SetRouterConfigGeoipsite(config.GetRouterConfigGeoipsite());
    }

    obj.SaveToFile(GetClientConfigPath());
}


/**
 * @brief TaskInfo::openLogFileDialog
 * @abstract 打开日志文件
 * @param errInfo
 */
void ConfigManager::openLogFileDialog()
{
    QString fileDir = getAbsolutePath(GetConfigs().GetLogFilePath());
    bool is_open = QDesktopServices::openUrl(QUrl(QString("file:///") + fileDir));
    if(!is_open)
    {
        qDebug()<<"log file open failed "<<is_open;
        return;
    }
}

void ConfigManager::addConnectionFromShareLink(QString shareLink)
{
    TrojanGoManger::parseShareLink(shareLink, getShareLinkConfigPath());
    QTrojanGoClientConfigJsonObject qConfigJsonObject = QTrojanGoClientConfigJsonObject::GetFromFile(getShareLinkConfigPath());
    QConfigJsonObject::QConnectionConfigJsonObject obj = QConfigJsonObject::QConnectionConfigJsonObject::NewFromClientConfigJson(&qConfigJsonObject);
    AddConnectionConfig(obj);
}
