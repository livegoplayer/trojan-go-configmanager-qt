#ifndef QTROJANGOCLIENTCONFIGJSONOBJECT_H
#define QTROJANGOCLIENTCONFIGJSONOBJECT_H

#include <QJsonObject>



class QTrojanGoClientConfigJsonObject: public QJsonObject
{
public:
    QTrojanGoClientConfigJsonObject();
    // loglevel
    static const int ALL = 0;
    static const int INFO = 1;
    static const int WARN = 2;
    static const int ERROR = 3;
    static const int Fatal = 4;
    static const int NONE = 5;

    // logfile
    constexpr static const char DEFAULT_LOG_FILE_PATH[] = "$PROGRAM_DIR$/log/client.log"; // 未指定则使用标准输出

    // default serveraddress and port
    constexpr static const char DEFAULT_LOCAL_ADDRESS[] = "127.0.0.1";
    static const int DEFAULT_LOCAL_PORT = 8080;
    static const int DEFAULT_LOG_LEVEL = 1;

    constexpr static const char DEFAULT_REMOTE_ADDRESS[] = "example.com";
    static const int DEFAULT_REMOTE_PORT = 443;
    constexpr static const char DEFAULT_RUN_TYPE[] = "client";
    static const bool DEFAULT_DISABLE_HTTP_CHECK = false;
    static const int DEFAULT_UDP_TIMMEOUT = 60;


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
    constexpr static const char DEFAULT_ROUTER_DEFALUT_POLICY[] = "proxy";
    constexpr static const char DEFAULT_ROUTER_DOMAIN_STRATEGY[] = "as_is";
    constexpr static const char DEFAULT_ROUTER_GEOIP[] = "$PROGRAM_DIR$/geoip.dat";
    constexpr static const char DEFAULT_ROUTER_GEOSITE[] = "$PROGRAM_DIR$/geosite.dat";

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


    // 根配置
    constexpr static const char runTypeKey[] = "client";
    constexpr static const char localAddrKey[] = "local_addr";
    constexpr static const char localPortKey[] = "local_port";
    constexpr static const char remoteAddrKey[] = "remote_addr";
    constexpr static const char remotePortKey[] = "remote_port";
    constexpr static const char passwordKey[] = "password";
    constexpr static const char disableHttpCheckKey[] = "disable_http_check";
    constexpr static const char udpTimeoutKey[] = "udp_timeout";

    // log
    constexpr static const char logLevelKey[] = "log_level";
    constexpr static const char logFileKey[] = "log_file";

    // router配置
    constexpr static const char routerKey[] = "router";
    constexpr static const char routerByPassKey[] = "bypass";
    constexpr static const char routerBlockKey[] = "block";
    constexpr static const char routerProxyKey[] = "proxy";
    constexpr static const char routerDefaultPolicyKey[] = "default_policy";
    constexpr static const char routerDomainStrategyKey[] = "domain_strategy";
    constexpr static const char routerGeoipKey[] = "geoip";
    constexpr static const char routerGeositeKey[] = "geosite";
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


    static QJsonObject getDefaulTcpObj();
    static QJsonObject getDefaultRouterObj();
    static QJsonObject getDefaulMuxObj();
    static QJsonObject getDefaulSSLObj();
    static QJsonArray getDefaultSSLAlpnList();
    static QTrojanGoClientConfigJsonObject GetDefaulObj();
    int GetLastConnectItem();
    QTrojanGoClientConfigJsonObject *SetLastConnectItem(int item);
    QJsonObject GetMuxConfig();
    int GetMuxConfigConcurrency();
    QTrojanGoClientConfigJsonObject *SetMuxConfigEnabled(bool MuxEnabled);
    int GetMuxConfigIdleTimeout();
    bool GetMuxConfigEnabled();
    QJsonObject GetTCPConfig();
    bool GetTCPConfigNoDelay();
    QTrojanGoClientConfigJsonObject *SetTCPConfigNoDelay(bool TCPNoDelay);
    bool GetTCPConfigKeepAlive();
    QTrojanGoClientConfigJsonObject *SetTCPConfigKeepAlive(bool TCPKeepAlive);
    QTrojanGoClientConfigJsonObject *SetTCPPreferIpv4(bool TCPPreferIpv4);
    bool GetTCPConfigPreferIpv4();
    QTrojanGoClientConfigJsonObject *SetMuxConfigIdleTimeout(bool MuxIdleTimeout);
    QJsonObject GetRouterConfig();
    bool GetRouterConfigByPsssEnabled();
    QTrojanGoClientConfigJsonObject *SetRouterConfigByPsssEnabled(bool RouterByPsssEnabled);
    bool GetRouterConfigProxyEnabled();
    QTrojanGoClientConfigJsonObject *SetRouterConfigProxyEnabled(bool RouterProxyEnabled);
    bool GetRouterConfigBlockEnabled();
    QTrojanGoClientConfigJsonObject *SetRouterConfigBlockEnable(bool RouterBlockEnable);
    void SaveToFile(QString path);
    QJsonArray GetRouterConfigByPsssList();
    QTrojanGoClientConfigJsonObject *SetRouterConfigByPsssList(QJsonArray RouterByPsssList);
    QJsonArray GetRouterConfigProxyList();
    QTrojanGoClientConfigJsonObject *SetRouterConfigProxyList(QJsonArray RouterProxyList);
    QJsonArray GetRouterConfigBlockList(QJsonObject jsonObject);
    QTrojanGoClientConfigJsonObject *SetRouterConfigBlockList(QJsonArray RouterBlockList);
    QJsonArray GetConnectionList();
    QJsonArray GetRouterConfigBlockList();
    QString GetLocalAddr();
    int GetLogLevel();
    QTrojanGoClientConfigJsonObject *SetLogLevel(int LogLevel);
    QTrojanGoClientConfigJsonObject *SetLocalAddr(QString LocalAddr);
    int GetLocalPort(QJsonObject jsonObject);
    QTrojanGoClientConfigJsonObject *SetLocalPort(int localPort);
    int GetLocalPort();
    QTrojanGoClientConfigJsonObject *AddConnectionConfig(QString name, QString server, QString lastDelay, QString lastUseTime, QString servePort, QString sni, QString password);
    QTrojanGoClientConfigJsonObject *EditConnectionConfig(int Index, QString name, QString server, QString lastDelay, QString lastUseTime, QString servePort, QString sni, QString password);
    QTrojanGoClientConfigJsonObject *DelConnectionConfig(int index);
    QTrojanGoClientConfigJsonObject *UpConnectionConfig(int index);
    static QTrojanGoClientConfigJsonObject GetFromFile(QString sFile);
    QTrojanGoClientConfigJsonObject *SetMuxConfigConcurrency(int MuxConcurrency);
    QTrojanGoClientConfigJsonObject *SetMuxConfigIdleTimeout(int MuxIdleTimeout);
    int GetRemotePort();
    QTrojanGoClientConfigJsonObject *SetRemotePort(int localPort);
    QTrojanGoClientConfigJsonObject *SetRemoteAddr(QString LocalAddr);
    QString GetRemoteAddr();
    QTrojanGoClientConfigJsonObject *SetRunType(QString type);
    QString GetRunType();
    QJsonArray GetPasswordList();
    QTrojanGoClientConfigJsonObject *SetPasswordList(QJsonArray arr);
    static bool confirmFile(QString sFile);
    QString GetLogFilePath();
    QTrojanGoClientConfigJsonObject *SetLogFilePath(QString path);
    bool GetDisableHttpCheckKey();
    int GetUDPTimeoutKey();
    QTrojanGoClientConfigJsonObject *SetUDPTimeoutKey(int val);
    QJsonObject GetSSLConfig();
    bool GetSSLConfigVerify();
    QTrojanGoClientConfigJsonObject *SetSSLConfigVerify(bool val);
    QTrojanGoClientConfigJsonObject *SetSSLConfigVerifyHostname(bool val);
    bool GetSSLConfigVerifyHostname();
    QString GetSSLConfigCert();
    QTrojanGoClientConfigJsonObject *SetSSLConfigCert(QString val);
    QTrojanGoClientConfigJsonObject *SetSSLConfigKey(QString val);
    QString GetSSLConfigKey();
    QString GetSSLConfigKeyPassword();
    QTrojanGoClientConfigJsonObject *SetSSLConfigKeyPassword(QString val);
    QTrojanGoClientConfigJsonObject *SetSSLConfigCurves(QString val);
    QString GetSSLConfigCurves();
    bool GetSSLConfigPreferServerCipher();
    QTrojanGoClientConfigJsonObject *SetSSLConfigPreferServerCipher(bool val);
    QString GetSSLConfigSni();
    QTrojanGoClientConfigJsonObject *SetSSLConfigSni(QString val);
    QJsonArray GetSSLConfigAlpn();
    QTrojanGoClientConfigJsonObject *SetSSLConfigAlpn(QJsonArray arr);
    bool GetSSLConfigSessionTicket();
    QTrojanGoClientConfigJsonObject *SetSSLConfigSessionTicket(bool val);
    bool GetSSLConfigReuseSession();
    QTrojanGoClientConfigJsonObject *SetSSLConfigReuseSession(bool val);
    QString GetSSLPlainHttpResponse();
    QTrojanGoClientConfigJsonObject *SetSSLConfigPlainHttpResponse(QString val);
    QTrojanGoClientConfigJsonObject *SetSSLConfigFallbackAddr(QString val);
    QString GetSSLFallbackAddr();
    QTrojanGoClientConfigJsonObject *SetSSLConfigFallbackPort(int val);
    int GetSSLFallbackPort();
    QString GetSSLConfigFingerprint();
    QTrojanGoClientConfigJsonObject *SetDisableHttpCheckKey(bool val);
    QTrojanGoClientConfigJsonObject *SetRouterConfigEnabled(bool value);
    bool GetRouterConfigEnabled();
    QString GetRouterConfigDefaultPolicy();
    QTrojanGoClientConfigJsonObject *SetRouterConfigDefaultPolicy(QString value);
    QString GetRouterConfigDomainStrategy();
    QTrojanGoClientConfigJsonObject *SetRouterConfigDomainStrategy(QString value);
    QString GetRouterConfigGeoip();
    QTrojanGoClientConfigJsonObject *SetRouterConfigGeoip(QString value);
    QString GetRouterConfigGeoipsite();
    QTrojanGoClientConfigJsonObject *SetRouterConfigGeoipsite(QString value);
    QTrojanGoClientConfigJsonObject *SetSSLConfigCipher(QString val);
    QString GetSSLConfigCipher();
    QTrojanGoClientConfigJsonObject *SetSSLConfigFingerprint(QString val);
};

#endif // QTROJANGOCLIENTCONFIGJSONOBJECT_H
