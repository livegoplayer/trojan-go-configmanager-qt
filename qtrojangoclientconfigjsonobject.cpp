#include "qtrojangoclientconfigjsonobject.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <qdir.h>

QTrojanGoClientConfigJsonObject::QTrojanGoClientConfigJsonObject()
{


}

// 获取默认tcp配置
QJsonObject QTrojanGoClientConfigJsonObject::getDefaulTcpObj() {
    QJsonObject *tcpObject = new QJsonObject();
    tcpObject->insert(tcpNoDelayKey, DEFAULT_TCP_NO_DELAY);
    tcpObject->insert(tcpKeepAliveKey, DEFAULT_TCP_KEEP_ALIVE);
    tcpObject->insert(tcpPreferIpv4Key, DEFAULT_TCP_PREFER_IPV4);
    return *tcpObject;
}

// 获取默认router配置
QJsonObject QTrojanGoClientConfigJsonObject::getDefaultRouterObj() {
    QJsonArray *emptyArray = new QJsonArray();
    QJsonObject *routerObject = new QJsonObject();
    routerObject->insert(routerEnableKey, DEFAULT_ROUTER_ENABLED);
    routerObject->insert(routerByPassKey, *emptyArray);
    routerObject->insert(routerProxyKey, *emptyArray);
    routerObject->insert(routerBlockKey, *emptyArray);
    routerObject->insert(routerDefaultPolicyKey, DEFAULT_ROUTER_DEFALUT_POLICY);
    routerObject->insert(routerDomainStrategyKey, DEFAULT_ROUTER_DOMAIN_STRATEGY);
    routerObject->insert(routerGeoipKey, DEFAULT_ROUTER_GEOIP);
    routerObject->insert(routerGeositeKey, DEFAULT_ROUTER_GEOSITE);
    return *routerObject;
}

// 获取默认mux配置
QJsonObject QTrojanGoClientConfigJsonObject::getDefaulMuxObj() {
    QJsonObject *muxObject = new QJsonObject();
    muxObject->insert(muxEnabledKey, DEFAULT_TCP_NO_DELAY);
    muxObject->insert(muxConcurrencyKey, DEFAULT_MUX_CONCURRENCY);
    muxObject->insert(muxIdleTimeoutKey, DEFAULT_MUX_IDLE_TIME_OUT);
    return *muxObject;
}

// 获取默认ssl配置
QJsonObject QTrojanGoClientConfigJsonObject::getDefaulSSLObj() {
    QJsonObject *sslObject = new QJsonObject();
    sslObject->insert(sslVerifyKey, DEFAULT_SSL_VERIFY);
    sslObject->insert(sslVerifyHostnameKey, DEFAULT_SSL_VERIFY_HOSTNAME);
    sslObject->insert(sslCertKey, DEFAULT_SSL_CERT);
    sslObject->insert(sslKeyKey, DEFAULT_SSL_KEY);
    sslObject->insert(sslKeyPasswordKey, DEFAULT_SSL_KEY_PASSWORD);
    sslObject->insert(sslCipherKey, DEFAULT_SSL_CIPHER);
    sslObject->insert(sslCurvesKey, DEFAULT_SSL_CURVES);
    sslObject->insert(sslPreferServerCipherKey, DEFAULT_SSL_PREFER_SERVER_CIPHER);
    sslObject->insert(sslSniKey, DEFAULT_SSL_SNI);
    sslObject->insert(sslAlpnKey, getDefaultSSLAlpnList());
    sslObject->insert(sslSessionTicketKey, DEFAULT_SSL_SESSION_TICKET);
    sslObject->insert(sslReuseSessionKey, DEFAULT_SSL_REUSE_SESSION);
    sslObject->insert(sslPlainHttpResponseKey, DEFAULT_SSL_PLAIN_HTTP_RESPONSE);
    sslObject->insert(sslFallbackAddrKey, DEFAULT_SSL_FALLBACK_ADDR);
    sslObject->insert(sslFallbackPortKey, DEFAULT_SSL_FALLBACK_PORT);
    sslObject->insert(sslFingerprintKey, DEFAULT_SSL_FINGERPRINT);
    return *sslObject;
}

QJsonArray QTrojanGoClientConfigJsonObject::getDefaultSSLAlpnList() {
    QJsonArray *arr = new QJsonArray();
    arr->append("http/1.1");
    return *arr;
}

// 获取默认配置
QTrojanGoClientConfigJsonObject QTrojanGoClientConfigJsonObject::GetDefaulObj() {
    QTrojanGoClientConfigJsonObject *obj = new QTrojanGoClientConfigJsonObject();
    QJsonArray *emptyArray = new QJsonArray();
    obj->insert(runTypeKey, DEFAULT_RUN_TYPE);
    obj->insert(localAddrKey, DEFAULT_LOCAL_ADDRESS);
    obj->insert(localPortKey, DEFAULT_LOCAL_PORT);
    obj->insert(remoteAddrKey, DEFAULT_REMOTE_ADDRESS);
    obj->insert(remotePortKey, DEFAULT_REMOTE_PORT);
    obj->insert(logLevelKey, INFO);
    obj->insert(logFileKey, DEFAULT_LOG_FILE_PATH);
    obj->insert(passwordKey, *emptyArray);
    obj->insert(disableHttpCheckKey, DEFAULT_DISABLE_HTTP_CHECK);
    obj->insert(udpTimeoutKey, DEFAULT_DISABLE_HTTP_CHECK);
    obj->insert(tcpKey, getDefaulTcpObj());
    obj->insert(muxKey, getDefaulMuxObj());
    obj->insert(routerKey, getDefaultRouterObj());
    obj->insert(sslKey, getDefaulSSLObj());
    return *obj;
}

QJsonObject QTrojanGoClientConfigJsonObject::GetMuxConfig(){
    if(this->contains(muxKey))
    {
        QJsonValue config = this->value(muxKey);
        return config.toObject();
    }
    return getDefaulMuxObj();
}

int QTrojanGoClientConfigJsonObject::GetMuxConfigConcurrency(){
    QJsonObject muxConfig = this->GetMuxConfig();

    if(muxConfig.contains(muxConcurrencyKey))
    {
        QJsonValue config = muxConfig.value(muxConcurrencyKey);
        return config.toInt();
    }
    return DEFAULT_MUX_CONCURRENCY;
}

QTrojanGoClientConfigJsonObject *QTrojanGoClientConfigJsonObject::SetMuxConfigConcurrency(int MuxConcurrency){
    QJsonObject muxConfig = this->GetMuxConfig();
    muxConfig.insert(muxConcurrencyKey, MuxConcurrency);
    this->insert(muxKey, muxConfig);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetMuxConfigEnabled(){
    QJsonObject muxConfig = this->GetMuxConfig();
    if(muxConfig.contains(muxEnabledKey))
    {
        QJsonValue config = muxConfig.value(muxEnabledKey);
        return config.toBool();
    }
    return DEFAULT_MUX_ENABLED;
}

QTrojanGoClientConfigJsonObject *QTrojanGoClientConfigJsonObject::SetMuxConfigEnabled( bool MuxEnabled){
    QJsonObject muxConfig = this->GetMuxConfig();
    muxConfig.insert(muxEnabledKey, MuxEnabled);
    this->insert(muxKey, muxConfig);
    return this;
}

int QTrojanGoClientConfigJsonObject::GetMuxConfigIdleTimeout(){
    QJsonObject muxConfig = this->GetMuxConfig();
    if(muxConfig.contains(muxIdleTimeoutKey))
    {
        QJsonValue config = muxConfig.value(muxIdleTimeoutKey);
        return config.toInt();
    }
    return DEFAULT_MUX_IDLE_TIME_OUT;
}

QTrojanGoClientConfigJsonObject *QTrojanGoClientConfigJsonObject::SetMuxConfigIdleTimeout(int MuxIdleTimeout){
    QJsonObject muxConfig = this->GetMuxConfig();
    muxConfig.insert(muxIdleTimeoutKey, MuxIdleTimeout);
    this->insert(muxKey, muxConfig);
    return this;
}

QJsonObject QTrojanGoClientConfigJsonObject::GetTCPConfig(){
    if(this->contains(tcpKey))
    {
        QJsonValue config = this->value(tcpKey);
        return config.toObject();
    }
    return QTrojanGoClientConfigJsonObject::getDefaulTcpObj();
}

bool QTrojanGoClientConfigJsonObject::GetTCPConfigNoDelay(){
    QJsonObject tcpConfig = this->GetTCPConfig();
    if(tcpConfig.contains(tcpNoDelayKey))
    {
        QJsonValue config = tcpConfig.value(tcpNoDelayKey);
        return config.toBool();
    }
    return DEFAULT_TCP_NO_DELAY;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetTCPConfigNoDelay(bool TCPNoDelay){
    QJsonObject tcpConfig = this->GetTCPConfig();
    tcpConfig.insert(tcpNoDelayKey, TCPNoDelay);
    this->insert(tcpKey, tcpConfig);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetTCPConfigKeepAlive(){
    QJsonObject tcpConfig = this->GetTCPConfig();
    if(tcpConfig.contains(tcpKeepAliveKey))
    {
        QJsonValue config = tcpConfig.value(tcpKeepAliveKey);
        return config.toBool();
    }
    return DEFAULT_TCP_KEEP_ALIVE;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetTCPConfigKeepAlive(bool TCPKeepAlive){
    QJsonObject tcpConfig = this->GetTCPConfig();
    tcpConfig.insert(tcpKeepAliveKey, TCPKeepAlive);
    this->insert(tcpKey, tcpConfig);
    return this;
}


bool QTrojanGoClientConfigJsonObject::GetTCPConfigPreferIpv4(){
    QJsonObject tcpConfig = this->GetTCPConfig();
    if(tcpConfig.contains(tcpPreferIpv4Key))
    {
        QJsonValue config = tcpConfig.value(tcpPreferIpv4Key);
        return config.toBool();
    }
    return DEFAULT_TCP_PREFER_IPV4;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetTCPPreferIpv4(bool TCPPreferIpv4){
    QJsonObject tcpConfig = this->GetTCPConfig();
    tcpConfig.insert(tcpPreferIpv4Key, TCPPreferIpv4);
    this->insert(tcpKey, tcpConfig);
    return this;
}

QJsonObject QTrojanGoClientConfigJsonObject::GetRouterConfig(){
    if(this->contains(routerKey))
    {
        QJsonValue config = this->value(routerKey);
        return config.toObject();
    }
    return getDefaultRouterObj();
}


QJsonArray QTrojanGoClientConfigJsonObject::GetRouterConfigByPsssList(){
    QJsonObject routerConfig = this->GetRouterConfig();

    if(routerConfig.contains(routerByPassKey))
    {
        QJsonValue config = routerConfig.value(routerByPassKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();
    return *emptyArray;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigByPsssList(QJsonArray RouterByPsssList){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerByPassKey, RouterByPsssList);
    this->insert(routerKey, routerConfig);
    return this;
}

QJsonArray QTrojanGoClientConfigJsonObject::GetRouterConfigProxyList(){
    QJsonObject routerConfig = this->GetRouterConfig();

    if(routerConfig.contains(routerProxyKey))
    {
        QJsonValue config = routerConfig.value(routerProxyKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();

    return *emptyArray;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigProxyList(QJsonArray RouterProxyList){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerProxyKey, RouterProxyList);
    this->insert(routerKey, routerConfig);
    return this;
}


bool QTrojanGoClientConfigJsonObject::GetRouterConfigEnabled(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerEnableKey))
    {
        QJsonValue config = routerConfig.value(routerEnableKey);
        return config.toBool();
    }

    return DEFAULT_ROUTER_ENABLED;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigEnabled(bool value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerEnableKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}


QString QTrojanGoClientConfigJsonObject::GetRouterConfigDefaultPolicy(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerDefaultPolicyKey))
    {
        QJsonValue config = routerConfig.value(routerDefaultPolicyKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_DEFALUT_POLICY;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigDefaultPolicy(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerDefaultPolicyKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}


QString QTrojanGoClientConfigJsonObject::GetRouterConfigDomainStrategy(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerDomainStrategyKey))
    {
        QJsonValue config = routerConfig.value(routerDomainStrategyKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_DOMAIN_STRATEGY;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigDomainStrategy(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerDomainStrategyKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetRouterConfigGeoip(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerGeoipKey))
    {
        QJsonValue config = routerConfig.value(routerGeoipKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_GEOIP;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigGeoip(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerGeoipKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetRouterConfigGeoipsite(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerGeositeKey))
    {
        QJsonValue config = routerConfig.value(routerGeositeKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_GEOSITE;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigGeoipsite(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerGeositeKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}

QJsonArray QTrojanGoClientConfigJsonObject::GetRouterConfigBlockList(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerBlockKey))
    {
        QJsonValue config = routerConfig.value(routerBlockKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();
    return *emptyArray;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRouterConfigBlockList(QJsonArray RouterBlockList){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerBlockKey, RouterBlockList);
    this->insert(routerKey, routerConfig);
    return this;
}

// ssl config相关
QJsonObject QTrojanGoClientConfigJsonObject::GetSSLConfig(){
    if(this->contains(sslKey))
    {
        QJsonValue config = this->value(sslKey);
        return config.toObject();
    }
    return QTrojanGoClientConfigJsonObject::getDefaulSSLObj();
}

bool QTrojanGoClientConfigJsonObject::GetSSLConfigVerify(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslVerifyKey))
    {
        QJsonValue config = sslConfig.value(sslVerifyKey);
        return config.toBool();
    }
    return DEFAULT_SSL_VERIFY;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigVerify(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslVerifyKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigVerifyHostname(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslVerifyHostnameKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetSSLConfigVerifyHostname(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslVerifyHostnameKey))
    {
        QJsonValue config = sslConfig.value(sslVerifyHostnameKey);
        return config.toBool();
    }
    return DEFAULT_SSL_VERIFY_HOSTNAME;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigCert(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslCertKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigCert(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslCertKey))
    {
        QJsonValue config = sslConfig.value(sslCertKey);
        return config.toString();
    }
    return DEFAULT_SSL_CERT;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigKey(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslKeyKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigKey(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslKeyKey))
    {
        QJsonValue config = sslConfig.value(sslKeyKey);
        return config.toString();
    }
    return DEFAULT_SSL_KEY;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigKeyPassword(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslKeyPasswordKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigKeyPassword(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslKeyKey))
    {
        QJsonValue config = sslConfig.value(sslKeyPasswordKey);
        return config.toString();
    }
    return DEFAULT_SSL_KEY_PASSWORD;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigCurves(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslCurvesKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigCurves(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslCurvesKey))
    {
        QJsonValue config = sslConfig.value(sslCurvesKey);
        return config.toString();
    }
    return DEFAULT_SSL_CURVES;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigCipher(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslCipherKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigCipher(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslCipherKey))
    {
        QJsonValue config = sslConfig.value(sslCipherKey);
        return config.toString();
    }
    return DEFAULT_SSL_CIPHER;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigPreferServerCipher(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslPreferServerCipherKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetSSLConfigPreferServerCipher(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslPreferServerCipherKey))
    {
        QJsonValue config = sslConfig.value(sslPreferServerCipherKey);
        return config.toBool();
    }
    return DEFAULT_SSL_PREFER_SERVER_CIPHER;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigSni(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslSniKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigSni(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslSniKey))
    {
        QJsonValue config = sslConfig.value(sslSniKey);
        return config.toString();
    }
    return DEFAULT_SSL_SNI;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigAlpn(QJsonArray arr){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslAlpnKey, arr);
    this->insert(sslKey, sslConfig);
    return this;
}

QJsonArray QTrojanGoClientConfigJsonObject::GetSSLConfigAlpn(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslAlpnKey))
    {
        QJsonValue config = sslConfig.value(sslAlpnKey);
        return config.toArray();
    }
    return getDefaultSSLAlpnList();
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigSessionTicket(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslSessionTicketKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetSSLConfigSessionTicket(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslSessionTicketKey))
    {
        QJsonValue config = sslConfig.value(sslSessionTicketKey);
        return config.toBool();
    }
    return DEFAULT_SSL_SESSION_TICKET;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigReuseSession(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslReuseSessionKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetSSLConfigReuseSession(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslReuseSessionKey))
    {
        QJsonValue config = sslConfig.value(sslReuseSessionKey);
        return config.toBool();
    }
    return DEFAULT_SSL_REUSE_SESSION;
}


QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigPlainHttpResponse(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslPlainHttpResponseKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLPlainHttpResponse(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslPlainHttpResponseKey))
    {
        QJsonValue config = sslConfig.value(sslPlainHttpResponseKey);
        return config.toString();
    }
    return DEFAULT_SSL_PLAIN_HTTP_RESPONSE;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigFallbackAddr(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslFallbackAddrKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLFallbackAddr(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslFallbackAddrKey))
    {
        QJsonValue config = sslConfig.value(sslFallbackAddrKey);
        return config.toString();
    }
    return DEFAULT_SSL_FALLBACK_ADDR;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigFallbackPort(int val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslFallbackPortKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

int QTrojanGoClientConfigJsonObject::GetSSLFallbackPort(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslFallbackPortKey))
    {
        QJsonValue config = sslConfig.value(sslFallbackPortKey);
        return config.toInt();
    }
    return DEFAULT_SSL_FALLBACK_PORT;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetSSLConfigFingerprint(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslFingerprintKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetSSLConfigFingerprint(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslFingerprintKey))
    {
        QJsonValue config = sslConfig.value(sslFingerprintKey);
        return config.toString();
    }
    return DEFAULT_SSL_FINGERPRINT;
}


// 根配置相关
int QTrojanGoClientConfigJsonObject::GetLogLevel(){
    if(this->contains(logLevelKey))
    {
        QJsonValue config = this->value(logLevelKey);
        return config.toInt();
    }
    return DEFAULT_LOG_LEVEL;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetLogLevel(int value){
    this->insert(logLevelKey, value);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetLocalAddr(){
    if(this->contains(localAddrKey))
    {
        QJsonValue localAddr = this->value(localAddrKey);
        return localAddr.toString();
    }
    return DEFAULT_LOCAL_ADDRESS;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetLocalAddr(QString LocalAddr){
    this->insert(localAddrKey, LocalAddr);
    return this;
}

int QTrojanGoClientConfigJsonObject::GetLocalPort(){
    if(this->contains(localPortKey))
    {
        QJsonValue localPort = this->value(localPortKey);
        return localPort.toInt();
    }
    return DEFAULT_LOCAL_PORT;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetLocalPort(int localPort){
    this->insert(localPortKey, localPort);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetRemoteAddr(){
    if(this->contains(remoteAddrKey))
    {
        QJsonValue addr = this->value(remoteAddrKey);
        return addr.toString();
    }
    return DEFAULT_REMOTE_ADDRESS;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRemoteAddr(QString RemoteAddr){
    this->insert(remoteAddrKey, RemoteAddr);
    return this;
}

int QTrojanGoClientConfigJsonObject::GetRemotePort(){
    if(this->contains(remoteAddrKey))
    {
        QJsonValue port = this->value(remoteAddrKey);
        return port.toInt();
    }
    return DEFAULT_REMOTE_PORT;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRemotePort(int port){
    this->insert(remoteAddrKey, port);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetRunType(){
    if(this->contains(runTypeKey))
    {
        QJsonValue runType = this->value(runTypeKey);
        return runType.toString();
    }
    return DEFAULT_RUN_TYPE;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetRunType(QString type){
    this->insert(runTypeKey, type);
    return this;
}

QString QTrojanGoClientConfigJsonObject::GetLogFilePath(){
    if(this->contains(logFileKey))
    {
        QJsonValue config = this->value(logFileKey);
        return config.toString();
    }
    return DEFAULT_LOG_FILE_PATH;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetLogFilePath(QString path){
    this->insert(logFileKey, path);
    return this;
}

bool QTrojanGoClientConfigJsonObject::GetDisableHttpCheckKey(){
    if(this->contains(disableHttpCheckKey))
    {
        QJsonValue config = this->value(disableHttpCheckKey);
        return config.toBool();
    }
    return DEFAULT_DISABLE_HTTP_CHECK;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetDisableHttpCheckKey(bool val){
    this->insert(logFileKey, val);
    return this;
}


int QTrojanGoClientConfigJsonObject::GetUDPTimeoutKey(){
    if(this->contains(udpTimeoutKey))
    {
        QJsonValue config = this->value(udpTimeoutKey);
        return config.toInt();
    }
    return DEFAULT_UDP_TIMMEOUT;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetUDPTimeoutKey(int val){
    this->insert(udpTimeoutKey, val);
    return this;
}

QJsonArray QTrojanGoClientConfigJsonObject::GetPasswordList(){
    if(this->contains(passwordKey))
    {
        QJsonValue config = this->value(passwordKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();
    return *emptyArray;
}

QTrojanGoClientConfigJsonObject* QTrojanGoClientConfigJsonObject::SetPasswordList(QJsonArray arr){
    this->insert(passwordKey, arr);
    return this;
}


// 文件操作相关
bool QTrojanGoClientConfigJsonObject::confirmFile(QString sFile)
{
    QString sPath = sFile.left(sFile.lastIndexOf('/'));

    //文件是否存在
    QDir dir(sPath);
    if(!dir.exists(sPath))
    {
        //路径不存在，则创建路径
        if(!dir.mkdir(sPath))
            return false;//路径创建失败就没办法了，通常不会失败
    }
    //到这里需确认路径已经ok，且文件不存在，创建文件
    QFile file(sFile);
    //当以Write方式打开时，若文件不存在则自动创建
    if(!file.open(QFileDevice::WriteOnly | QFileDevice::Append)){
        file.close();
        return false;
    }
    file.close();
    QFile sfile(sFile);
    sfile.open(QFileDevice::ReadOnly);
    QString value = sfile.readAll();
    sfile.close();

    if (value.length() == 0) {
        // 初始化json
        QFile nfile(sFile);
        nfile.open(QFileDevice::WriteOnly |QFileDevice::Truncate);
        QTrojanGoClientConfigJsonObject obj = GetDefaulObj();
        QJsonDocument *document = new QJsonDocument();
        document->setObject(obj);
        nfile.write(document->toJson());
        nfile.close();
    }
    return true;
}

QTrojanGoClientConfigJsonObject QTrojanGoClientConfigJsonObject::GetFromFile(QString sFile)
{

    if (!confirmFile(sFile)) {
        return  *(new QTrojanGoClientConfigJsonObject());
    }

    QFile file(sFile);
    file.open(QFileDevice::ReadOnly);
    QString value = file.readAll();

    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8());
    QJsonObject newObject = document.object();
    QTrojanGoClientConfigJsonObject jsonObject = static_cast<QTrojanGoClientConfigJsonObject&>(newObject);
    file.close();

    return jsonObject;
}

void QTrojanGoClientConfigJsonObject::SaveToFile(QString path){
    // 初始化json
    QFile nfile(path);
    nfile.open(QFileDevice::WriteOnly |QFileDevice::Truncate);
    QJsonDocument *document = new QJsonDocument();
    document->setObject(*this);
    nfile.write(document->toJson());
    nfile.close();
}
