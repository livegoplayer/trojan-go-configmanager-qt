#include "configmanager.h"
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QFile>
#include "qconfigjsonobject.h"
#include "qtrojangoclientconfigjsonobject.h"

// 配置管理类
ConfigManager::ConfigManager(QWidget *parent)
    : QWidget{parent}
{
    this->connectionPath="./config/connectionList.json";
    this->clientConfigPath="./client.json";

    this->connectionPath = this->getAbsolutePath(this->connectionPath);
    this->clientConfigPath = this->getAbsolutePath(this->clientConfigPath);
}

QString ConfigManager::getAbsolutePath(QString str)
{
    QString sAppPath = QCoreApplication::applicationDirPath();
    QString sFilePath = sAppPath+"/"+str;
    return sFilePath;
}

int ConfigManager::AddConnectionConfig(QConfigJsonObject::QConnectionConfigJsonObject obj)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(this->connectionPath);
    qConfigJsonObject.AddConnectionConfig(obj);
    this->SaveConfig(qConfigJsonObject);
    emit this->configFileUpdated();
    return 0;
}

int ConfigManager::EditConnectionConfig(int Index, QConfigJsonObject::QConnectionConfigJsonObject obj)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(this->connectionPath);
    qConfigJsonObject.EditConnectionConfig(Index, obj);
    this->SaveConfig(qConfigJsonObject);
    emit this->configFileUpdated();
    return 0;
}

int ConfigManager::DelConnectionConfig(int index)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(this->connectionPath);

    qConfigJsonObject.DelConnectionConfig(index);
    this->SaveConfig(qConfigJsonObject);

    emit this->configFileUpdated();
    return 0;
}


int ConfigManager::UpConnectionConfig(int index)
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(this->connectionPath);

    qConfigJsonObject.UpConnectionConfig(index);
    this->SaveConfig(qConfigJsonObject);

    emit this->configFileUpdated();
    return 0;
}


QConfigJsonObject ConfigManager::GetConfigs()
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(this->connectionPath);
    return qConfigJsonObject;
}

void ConfigManager::SaveConfig(QConfigJsonObject config)
{
    config.SaveToFile(this->connectionPath);
}


QConfigJsonObject::QConnectionConfigListJsonObject ConfigManager::GetConnectionConfigList()
{
    QConfigJsonObject qConfigJsonObject = QConfigJsonObject::GetFromFile(this->connectionPath);
    return qConfigJsonObject.GetConnectionList();
}

QConfigJsonObject::QConnectionConfigJsonObject ConfigManager::GetConnectionConfigItem(int index)
{
    return this->GetConnectionConfigList().At(index);
}

void ConfigManager::CreateClientConfigByItemIndex(int index)
{
    QConfigJsonObject config = this->GetConfigs();
    QConfigJsonObject::QConnectionConfigListJsonObject array = config.GetConnectionList();
    QConfigJsonObject::QConnectionConfigJsonObject configItem = array.At(index);
    QString name = configItem.GetName();
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

    obj.SaveToFile(this->clientConfigPath);
}
