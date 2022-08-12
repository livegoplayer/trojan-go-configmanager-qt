#ifndef QCONFIGJSONOBJECT_H
#define QCONFIGJSONOBJECT_H

#include "src/config/qtrojangoclientconfigjsonobject.h"

#include <QJsonObject>
#include <qjsonarray.h>

class QConfigJsonObject : public QJsonObject
{
public:

    // loglevel
    static const int ALL = 0;
    static const int INFO = 1;
    static const int WARN = 2;
    static const int ERROR = 3;
    static const int Fatal = 4;
    static const int NONE = 5;

    // default serveraddress and port
    constexpr static const char DEFAULT_LOCAL_ADDRESS[] = "127.0.0.1";
    static const int DEFAULT_LOCAL_PORT = 8080;
    static const int DEFAULT_LOG_LEVEL = INFO;
    constexpr static const char DEFAULT_LOG_FILE_PATH[] = "./client.log"; // 未指定则使用标准输出
    static const bool DEFAULT_DISABLE_HTTP_CHECK = false;
    static const int DEFAULT_UDP_TIMMEOUT = 60;
    static const bool DEFAULT_HIDE_CLOSE = true;
    static const bool DEFAULT_AUTO_CONNECT = false;

    // Theme
    static const int THEME_LIGHT = 0;
    static const int THEME_DARK = 1;
    static const int DEFAULT_THEME = THEME_LIGHT;

    // default tcp configs
    static const bool DEFAULT_TCP_NO_DELAY = true;
    static const bool DEFAULT_TCP_KEEP_ALIVE = true;
    static const bool DEFAULT_TCP_PREFER_IPV4 = false;

    // default mux configs
    static const bool DEFAULT_MUX_ENABLED = false;
    static const int DEFAULT_MUX_CONCURRENCY = 8;
    static const int DEFAULT_MUX_IDLE_TIME_OUT = 60;

    // default router configs
    static const bool DEFAULT_ROUTER_ENABLED = true;
    static const bool DEFAULT_ROUTER_BY_PASS_ENABLED = false;
    static const bool DEFAULT_ROUTER_PROXY_ENABLED = false;
    static const bool DEFAULT_ROUTER_BLOCK_ENABLED = false;

    constexpr static const char DEFAULT_ROUTER_DEFALUT_POLICY[] = "proxy";
    constexpr static const char DEFAULT_ROUTER_DOMAIN_STRATEGY[] = "as_is";
    constexpr static const char DEFAULT_ROUTER_GEOIP[] = "./dat/geoip.dat";
    constexpr static const char DEFAULT_ROUTER_GEOSITE[] = "./dat/geosite.dat";

    QConfigJsonObject();
    constexpr static const char connectionListKey[] = "connection_list";
    constexpr static const char lastConnectItemKey[] = "last_connect_item";

    constexpr static const char localAddrKey[] = "local_addr";
    constexpr static const char localPortKey[] = "local_port";

    // log
    constexpr static const char logLevelKey[] = "log_level";
    constexpr static const char disableHttpCheckKey[] = "disable_http_check";
    constexpr static const char udpTimeoutKey[] = "udp_timeout";
    constexpr static const char logFileKey[] = "log_file";


    // theme
    constexpr static const char themeKey[] = "theme";

    // hide when close
    constexpr static const char hideCloseKey[] = "hide_close";

    // autoconnect when open
    constexpr static const char autoConnectKey[] = "auto_connect";


    // router配置
    constexpr static const char routerKey[] = "router";
    constexpr static const char routerByPassKey[] = "bypass";
    constexpr static const char routerBlockKey[] = "block";
    constexpr static const char routerProxyKey[] = "proxy";
    constexpr static const char routerDefaultPolicyKey[] = "default_policy";
    constexpr static const char routerDomainStrategyKey[] = "domain_strategy";
    constexpr static const char routerGeoipKey[] = "geoip";
    constexpr static const char routerGeositeKey[] = "geosite";
    // 这三个key方便管理，不用每次开关都清除规则列表,但是真正的配置文件里面没有
    constexpr static const char routerByPassEnableKey[] = "bypass_enabled";
    constexpr static const char routerBlockEnableKey[] = "block_enabled";
    constexpr static const char routerProxyEnableKey[] = "proxy_enabled";
    // 这个键永久开启
    constexpr static const char routerEnableKey[] = "enabled";


    //tcp配置
    constexpr static const char tcpKey[] = "tcp";
    constexpr static const char tcpNoDelayKey[] = "no_delay";
    constexpr static const char tcpKeepAliveKey[] = "keep_alive";
    constexpr static const char tcpPreferIpv4Key[] = "prefer_ipv4";

    //mux配置
    constexpr static const char muxKey[] = "mux";
    constexpr static const char muxEnabledKey[] = "enabled";
    constexpr static const char muxConcurrencyKey[] = "concurrency";
    constexpr static const char muxIdleTimeoutKey[] = "idle_timeout";

    class QConnectionConfigJsonObject : public QJsonObject {
    public:

        // 以下的key归属于connectionListKey
        constexpr static const char nameKey[] = "name";
        constexpr static const char serverAddrKey[] = "server_addr";
        constexpr static const char serverPortKey[] = "server_port";
        constexpr static const char passwordKey[] = "password";
        constexpr static const char lastDelayKey[] = "last_delay_time";
        constexpr static const char lastUseTimeKey[] = "last_use_time";

        constexpr static const char DEFAULT_NAME[] = "未命名配置";
        constexpr static const char DEFAULT_PASSWORD[] = "";
        constexpr static const char DEFAULT_SERVER_ADDR[] = "";
        static const int DEFAULT_SERVER_PORT = 443;
        static const int DEFAULT_LAST_DELAY = 0;
        static const int DEFAULT_LAST_USE_TIMME = 0;

        // default ssl configs
        static const bool DEFAULT_SSL_VERIFY = true;
        static const bool DEFAULT_SSL_VERIFY_HOSTNAME = true;
        constexpr static const char DEFAULT_SSL_CERT[] = "";
        constexpr static const char DEFAULT_SSL_KEY[] = "";
        constexpr static const char DEFAULT_SSL_KEY_PASSWORD[] = "";
        constexpr static const char DEFAULT_SSL_CIPHER[] = "";
        constexpr static const char DEFAULT_SSL_CURVES[] = "";
        static const bool DEFAULT_SSL_PREFER_SERVER_CIPHER = false;
        constexpr static const char DEFAULT_SSL_SNI[] = "";
        static const bool DEFAULT_SSL_SESSION_TICKET = true;
        static const bool DEFAULT_SSL_REUSE_SESSION = true;
        constexpr static const char DEFAULT_SSL_PLAIN_HTTP_RESPONSE[] = "";
        constexpr static const char DEFAULT_SSL_FALLBACK_ADDR[] = "";
        static const int DEFAULT_SSL_FALLBACK_PORT = 0;
        constexpr static const char DEFAULT_SSL_FINGERPRINT[] = "";

        //ssl配置
        constexpr static const char sslKey[] = "ssl";
        constexpr static const char sslVerifyKey[] = "verify";
        constexpr static const char sslVerifyHostnameKey[] = "verify_hostname";
        constexpr static const char sslCertKey[] = "cert";
        constexpr static const char sslKeyKey[] = "key";
        constexpr static const char sslKeyPasswordKey[] = "key_password";
        constexpr static const char sslCipherKey[] = "cipher";
        constexpr static const char sslCurvesKey[] = "curves";
        constexpr static const char sslPreferServerCipherKey[] = "prefer_server_cipher";
        constexpr static const char sslSniKey[] = "sni";
        constexpr static const char sslAlpnKey[] = "alpn";
        constexpr static const char sslSessionTicketKey[] = "session_ticket";
        constexpr static const char sslReuseSessionKey[] = "reuse_session";
        constexpr static const char sslPlainHttpResponseKey[] = "plain_http_response";
        constexpr static const char sslFallbackAddrKey[] = "fallback_addr";
        constexpr static const char sslFallbackPortKey[] = "fallback_port";
        constexpr static const char sslFingerprintKey[] = "fingerprint";

        QString GetName();
        QConfigJsonObject::QConnectionConfigJsonObject *SetName(QString name);
        QString GetServerAddr();
        QConfigJsonObject::QConnectionConfigJsonObject *SetServerAddr(QString value);
        int GetServerPort();
        QConfigJsonObject::QConnectionConfigJsonObject *SetServerPort(int value);
        QString GetPassword();
        QConfigJsonObject::QConnectionConfigJsonObject *SetPassword(QString value);
        int GetLastDelay();
        QConfigJsonObject::QConnectionConfigJsonObject *SetLastDelay(int value);
        int GetLastUseTime();
        QConfigJsonObject::QConnectionConfigJsonObject *SetLastUseTime(int value);
        QJsonObject GetSSLConfig();
        bool GetSSLConfigVerify();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigVerify(bool val);
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigVerifyHostname(bool val);
        bool GetSSLConfigVerifyHostname();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigCert(QString val);
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigKey(QString val);
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigKeyPassword(QString val);
        QString GetSSLConfigKey();
        QString GetSSLConfigKeyPassword();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigCurves(QString val);
        QString GetSSLConfigCurves();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigPreferServerCipher(bool val);
        bool GetSSLConfigPreferServerCipher();
        QString GetSSLConfigSni();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigAlpn(QJsonArray arr);
        QJsonArray GetSSLConfigAlpn();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigSessionTicket(bool val);
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigReuseSession(bool val);
        bool GetSSLConfigSessionTicket();
        bool GetSSLConfigReuseSession();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigPlainHttpResponse(QString val);
        QString GetSSLPlainHttpResponse();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigFallbackAddr(QString val);
        QString GetSSLFallbackAddr();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigFallbackPort(int val);
        int GetSSLFallbackPort();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigFingerprint(QString val);
        QString GetSSLConfigFingerprint();
        static QJsonObject getDefaulSSLObj();
        static QJsonArray getDefaultSSLAlpnList();
        QString GetSSLConfigCert();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigSni(QString val);
        QConnectionConfigJsonObject();
        QConfigJsonObject::QConnectionConfigJsonObject *SetSSLConfigCipher(QString val);
        QString GetSSLConfigCipher();
        static QConfigJsonObject::QConnectionConfigJsonObject NewFromClientConfigJson(QTrojanGoClientConfigJsonObject *ConfigJsonObject);
    private:
        QConfigJsonObject::QConnectionConfigJsonObject *init();

    };

    class QConnectionConfigListJsonObject : public QJsonArray {

    public:
        QConfigJsonObject::QConnectionConfigJsonObject At(int Index);
    };

    static QJsonObject getDefaulTcpObj();
    static QJsonObject getDefaultRouterObj();
    static QJsonObject getDefaulMuxObj();
    static QConfigJsonObject GetDefaulObj();
    int GetLastConnectItem();
    QConfigJsonObject *SetLastConnectItem(int item);
    QJsonObject GetMuxConfig();
    int GetMuxConfigConcurrency();
    QConfigJsonObject *SetMuxConfigEnabled(bool MuxEnabled);
    int GetMuxConfigIdleTimeout();
    bool GetMuxConfigEnabled();
    QJsonObject GetTCPConfig();
    bool GetTCPConfigNoDelay();
    QConfigJsonObject *SetTCPConfigNoDelay(bool TCPNoDelay);
    bool GetTCPConfigKeepAlive();
    QConfigJsonObject *SetTCPConfigKeepAlive(bool TCPKeepAlive);
    QConfigJsonObject *SetTCPPreferIpv4(bool TCPPreferIpv4);
    bool GetTCPConfigPreferIpv4();
    QConfigJsonObject *SetMuxConfigIdleTimeout(bool MuxIdleTimeout);
    QJsonObject GetRouterConfig();
    bool GetRouterConfigByPsssEnabled();
    QConfigJsonObject *SetRouterConfigByPsssEnabled(bool RouterByPsssEnabled);
    bool GetRouterConfigProxyEnabled();
    QConfigJsonObject *SetRouterConfigProxyEnabled(bool RouterProxyEnabled);
    bool GetRouterConfigBlockEnabled();
    QConfigJsonObject *SetRouterConfigBlockEnable(bool RouterBlockEnable);
    void SaveToFile(QString path);
    QJsonArray GetRouterConfigByPsssList();
    QConfigJsonObject *SetRouterConfigByPsssList(QJsonArray RouterByPsssList);
    QJsonArray GetRouterConfigProxyList();
    QConfigJsonObject *SetRouterConfigProxyList(QJsonArray RouterProxyList);
    QJsonArray GetRouterConfigBlockList(QJsonObject jsonObject);
    QConfigJsonObject *SetRouterConfigBlockList(QJsonArray RouterBlockList);
    QJsonArray GetRouterConfigBlockList();
    QString GetLocalAddr();
    int GetLogLevel();
    QConfigJsonObject *SetLogLevel(int LogLevel);
    QConfigJsonObject *SetLocalAddr(QString LocalAddr);
    int GetLocalPort(QJsonObject jsonObject);
    QConfigJsonObject *SetLocalPort(int localPort);
    int GetLocalPort();
    QConfigJsonObject *DelConnectionConfig(int index);
    QConfigJsonObject *UpConnectionConfig(int index);
    static QConfigJsonObject GetFromFile(QString sFile);
    QConfigJsonObject *SetMuxConfigConcurrency(int MuxConcurrency);
    QConfigJsonObject *SetMuxConfigIdleTimeout(int MuxIdleTimeout);


    QConfigJsonObject::QConnectionConfigListJsonObject GetConnectionList();
    int GetUDPTimeoutKey();
    QConfigJsonObject *SetUDPTimeoutKey(QString val);
    QConfigJsonObject *SetDisableHttpCheckKey(QString val);
    bool GetDisableHttpCheckKey();
    QConfigJsonObject *SetLogFilePath(QString path);
    QString GetLogFilePath();
    bool GetRouterConfigEnabled();
    QConfigJsonObject *SetRouterConfigEnabled(bool value);
    QString GetRouterConfigDefaultPolicy();
    QConfigJsonObject *SetRouterConfigDefaultPolicy(QString value);
    QString GetRouterConfigDomainStrategy();
    QString GetRouterConfigGeoip();
    QConfigJsonObject *SetRouterConfigGeoip(bool value);
    QConfigJsonObject *SetRouterConfigDomainStrategy(QString value);
    QConfigJsonObject *SetRouterConfigGeoip(QString value);
    QString GetRouterConfigGeoipsite();
    QConfigJsonObject *SetRouterConfigGeoipsite(QString value);
    QConfigJsonObject *EditConnectionConfig(int Index, QConnectionConfigJsonObject obj);
    QConfigJsonObject *AddConnectionConfig(QConnectionConfigJsonObject obj);
    QConfigJsonObject *SetTheme(int value);
    int GetTheme();
    QConfigJsonObject *DownConnectionConfig(int index);
    bool GetHideClose();
    QConfigJsonObject *SetHideClose(bool value);
    QConfigJsonObject *SetLastDelayTime(int Index, int lastDelayTime);
    QConfigJsonObject *SetAutoConnect(bool value);
    bool GetAutoConnect();
private:
    static bool confirmFile(QString sFile);
};



#endif // QCONFIGJSONOBJECT_H
