#include "qconfigjsonobject.h"

#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <qdir.h>

// new 方法，需要初始化了，内部结构过于复杂
QConfigJsonObject::QConnectionConfigJsonObject::QConnectionConfigJsonObject (){
    this->init();
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::init() {
    this->SetName(QConnectionConfigJsonObject::DEFAULT_NAME)->
        SetPassword(QConnectionConfigJsonObject::DEFAULT_PASSWORD)->
        SetServerAddr(QConnectionConfigJsonObject::DEFAULT_SERVER_ADDR)->
        SetServerPort(QConnectionConfigJsonObject::DEFAULT_SERVER_PORT)->
        SetLastDelay(QConnectionConfigJsonObject::DEFAULT_LAST_DELAY)->
        SetLastUseTime(QConnectionConfigJsonObject::DEFAULT_LAST_USE_TIMME)->
        insert(sslKey, QConnectionConfigJsonObject::getDefaulSSLObj());
    return this;
}

// 内部类的操作方法
QConfigJsonObject::QConnectionConfigJsonObject QConfigJsonObject::QConnectionConfigListJsonObject::At(int Index){
    QJsonObject newObj = this->at(Index).toObject();
    QConfigJsonObject::QConnectionConfigJsonObject obj = static_cast<QConfigJsonObject::QConnectionConfigJsonObject&>(newObj);
    return obj;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetName(){
    if(this->contains(nameKey))
    {
        QJsonValue config = this->value(nameKey);
        return config.toString();
    }
    return DEFAULT_NAME;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetName(QString value){
    this->insert(nameKey, value);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetServerAddr(){
    if(this->contains(serverAddrKey))
    {
        QJsonValue config = this->value(serverAddrKey);
        return config.toString();
    }
    return DEFAULT_SERVER_ADDR;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetServerAddr(QString value){
    this->insert(serverAddrKey, value);
    return this;
}

int QConfigJsonObject::QConnectionConfigJsonObject::GetServerPort(){
    if(this->contains(serverPortKey))
    {
        QJsonValue config = this->value(serverPortKey);
        return config.toInt();
    }
    return DEFAULT_SERVER_PORT;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetServerPort(int value){
    this->insert(serverPortKey, value);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetPassword(){
    if(this->contains(passwordKey))
    {
        QJsonValue config = this->value(passwordKey);
        return config.toString();
    }
    return DEFAULT_PASSWORD;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetPassword(QString value){
    this->insert(passwordKey, value);
    return this;
}

int QConfigJsonObject::QConnectionConfigJsonObject::GetLastDelay(){
    if(this->contains(lastDelayKey))
    {
        QJsonValue config = this->value(lastDelayKey);
        return config.toInt();
    }
    return DEFAULT_LAST_DELAY;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetLastDelay(int value){
    this->insert(lastDelayKey, value);
    return this;
}

int QConfigJsonObject::QConnectionConfigJsonObject::GetLastUseTime(){
    if(this->contains(lastUseTimeKey))
    {
        QJsonValue config = this->value(lastUseTimeKey);
        return config.toInt();
    }
    return DEFAULT_LAST_USE_TIMME;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetLastUseTime(int value){
    this->insert(lastUseTimeKey, value);
    return this;
}

// 获取默认tcp配置
QJsonObject QConfigJsonObject::getDefaulTcpObj() {
    QJsonObject *tcpObject = new QJsonObject();
    tcpObject->insert(tcpNoDelayKey, DEFAULT_TCP_NO_DELAY);
    tcpObject->insert(tcpKeepAliveKey, DEFAULT_TCP_KEEP_ALIVE);
    tcpObject->insert(tcpPreferIpv4Key, DEFAULT_TCP_PREFER_IPV4);
    return *tcpObject;
}

// 获取默认router配置
QJsonObject QConfigJsonObject::getDefaultRouterObj() {
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
    // 单独管理列表开关的三个建，同步为真正的配置文件的时候会主动去除掉
    routerObject->insert(routerByPassEnableKey, DEFAULT_ROUTER_BY_PASS_ENABLED);
    routerObject->insert(routerBlockEnableKey, DEFAULT_ROUTER_BLOCK_ENABLED);
    routerObject->insert(routerProxyEnableKey, DEFAULT_ROUTER_PROXY_ENABLED);

    return *routerObject;
}

// 获取默认mux配置
QJsonObject QConfigJsonObject::getDefaulMuxObj() {
    QJsonObject *muxObject = new QJsonObject();
    muxObject->insert(muxEnabledKey, DEFAULT_TCP_NO_DELAY);
    muxObject->insert(muxConcurrencyKey, DEFAULT_MUX_CONCURRENCY);
    muxObject->insert(muxIdleTimeoutKey, DEFAULT_MUX_IDLE_TIME_OUT);
    return *muxObject;
}

// 获取默认ssl配置
QJsonObject QConfigJsonObject::QConnectionConfigJsonObject::getDefaulSSLObj() {
    QJsonObject *sslObject = new QJsonObject();
    sslObject->insert(sslVerifyKey, DEFAULT_SSL_VERIFY);
    sslObject->insert(sslVerifyHostnameKey, DEFAULT_SSL_VERIFY_HOSTNAME);
    sslObject->insert(sslCertKey, DEFAULT_SSL_CERT);
    sslObject->insert(sslKeyKey, DEFAULT_SSL_KEY);
    sslObject->insert(sslKeyPasswordKey, DEFAULT_SSL_KEY_PASSWORD);
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

QJsonArray QConfigJsonObject::QConnectionConfigJsonObject::getDefaultSSLAlpnList() {
    QJsonArray *arr = new QJsonArray();
    arr->append("http/1.1");
    return *arr;
}


// ssl config相关
QJsonObject QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfig(){
    if(this->contains(sslKey))
    {
        QJsonValue config = this->value(sslKey);
        return config.toObject();
    }
    return this->getDefaulSSLObj();
}

bool QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigVerify(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslVerifyKey))
    {
        QJsonValue config = sslConfig.value(sslVerifyKey);
        return config.toBool();
    }
    return DEFAULT_SSL_VERIFY;
}


QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigVerify(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslVerifyKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigVerifyHostname(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslVerifyHostnameKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigVerifyHostname(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslVerifyHostnameKey))
    {
        QJsonValue config = sslConfig.value(sslVerifyHostnameKey);
        return config.toBool();
    }
    return DEFAULT_SSL_VERIFY_HOSTNAME;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigCert(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslCertKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigCert(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslCertKey))
    {
        QJsonValue config = sslConfig.value(sslCertKey);
        return config.toString();
    }
    return DEFAULT_SSL_CERT;
}


QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigKey(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslKeyKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigKey(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslKeyKey))
    {
        QJsonValue config = sslConfig.value(sslKeyKey);
        return config.toString();
    }
    return DEFAULT_SSL_KEY;
}


QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigKeyPassword(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslKeyPasswordKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigKeyPassword(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslKeyKey))
    {
        QJsonValue config = sslConfig.value(sslKeyPasswordKey);
        return config.toString();
    }
    return DEFAULT_SSL_KEY_PASSWORD;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigCipher(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslCipherKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigCipher(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslCipherKey))
    {
        QJsonValue config = sslConfig.value(sslCipherKey);
        return config.toString();
    }
    return DEFAULT_SSL_CIPHER;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigCurves(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslCurvesKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigCurves(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslCurvesKey))
    {
        QJsonValue config = sslConfig.value(sslCurvesKey);
        return config.toString();
    }
    return DEFAULT_SSL_CURVES;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigPreferServerCipher(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslPreferServerCipherKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigPreferServerCipher(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslPreferServerCipherKey))
    {
        QJsonValue config = sslConfig.value(sslPreferServerCipherKey);
        return config.toBool();
    }
    return DEFAULT_SSL_PREFER_SERVER_CIPHER;
}


QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigSni(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslSniKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigSni(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslSniKey))
    {
        QJsonValue config = sslConfig.value(sslSniKey);
        return config.toString();
    }
    return DEFAULT_SSL_SNI;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigAlpn(QJsonArray arr){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslAlpnKey, arr);
    this->insert(sslKey, sslConfig);
    return this;
}

QJsonArray QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigAlpn(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslAlpnKey))
    {
        QJsonValue config = sslConfig.value(sslAlpnKey);
        return config.toArray();
    }
    return getDefaultSSLAlpnList();
}


QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigSessionTicket(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslSessionTicketKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigSessionTicket(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslSessionTicketKey))
    {
        QJsonValue config = sslConfig.value(sslSessionTicketKey);
        return config.toBool();
    }
    return DEFAULT_SSL_SESSION_TICKET;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigReuseSession(bool val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslReuseSessionKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

bool QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigReuseSession(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslReuseSessionKey))
    {
        QJsonValue config = sslConfig.value(sslReuseSessionKey);
        return config.toBool();
    }
    return DEFAULT_SSL_REUSE_SESSION;
}


QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigPlainHttpResponse(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslPlainHttpResponseKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLPlainHttpResponse(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslPlainHttpResponseKey))
    {
        QJsonValue config = sslConfig.value(sslPlainHttpResponseKey);
        return config.toString();
    }
    return DEFAULT_SSL_PLAIN_HTTP_RESPONSE;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigFallbackAddr(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslFallbackAddrKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLFallbackAddr(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslFallbackAddrKey))
    {
        QJsonValue config = sslConfig.value(sslFallbackAddrKey);
        return config.toString();
    }
    return DEFAULT_SSL_FALLBACK_ADDR;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigFallbackPort(int val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslFallbackPortKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

int QConfigJsonObject::QConnectionConfigJsonObject::GetSSLFallbackPort(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslFallbackPortKey))
    {
        QJsonValue config = sslConfig.value(sslFallbackPortKey);
        return config.toInt();
    }
    return DEFAULT_SSL_FALLBACK_PORT;
}

QConfigJsonObject::QConnectionConfigJsonObject* QConfigJsonObject::QConnectionConfigJsonObject::SetSSLConfigFingerprint(QString val){
    QJsonObject sslConfig = this->GetSSLConfig();
    sslConfig.insert(sslFingerprintKey, val);
    this->insert(sslKey, sslConfig);
    return this;
}

QString QConfigJsonObject::QConnectionConfigJsonObject::GetSSLConfigFingerprint(){
    QJsonObject sslConfig = this->GetSSLConfig();
    if(sslConfig.contains(sslFingerprintKey))
    {
        QJsonValue config = sslConfig.value(sslFingerprintKey);
        return config.toString();
    }
    return DEFAULT_SSL_FINGERPRINT;
}


// 获取默认配置
QConfigJsonObject QConfigJsonObject::GetDefaulObj() {
    QJsonArray *emptyArray = new QJsonArray();
    QJsonObject *newObj = new QJsonObject();
    QConfigJsonObject *obj = static_cast<QConfigJsonObject*>(newObj);
    obj->insert(connectionListKey, QJsonValue(*emptyArray));
    obj->insert(lastConnectItemKey, QJsonValue(-1));
    obj->insert(logLevelKey, INFO);
    obj->insert(localPortKey, DEFAULT_LOCAL_PORT);
    obj->insert(logFileKey, DEFAULT_LOG_FILE_PATH);
    obj->insert(disableHttpCheckKey, DEFAULT_DISABLE_HTTP_CHECK);
    obj->insert(udpTimeoutKey, DEFAULT_DISABLE_HTTP_CHECK);
    obj->insert(tcpKey, getDefaulTcpObj());
    obj->insert(muxKey, getDefaulMuxObj());
    obj->insert(routerKey, getDefaultRouterObj());
    return *obj;
}

int QConfigJsonObject::GetLastConnectItem()
{
    if(this->contains(lastConnectItemKey))
    {
        QJsonValue jsonValueList = this->value(lastConnectItemKey);
        return jsonValueList.toInt();
    }
    return -1;
}

QConfigJsonObject* QConfigJsonObject::SetLastConnectItem(int item)
{
    this->insert(this->lastConnectItemKey, item);
    return this;
}

QJsonObject QConfigJsonObject::GetMuxConfig(){
    if(this->contains(muxKey))
    {
        QJsonValue config = this->value(muxKey);
        return config.toObject();
    }
    return this->GetMuxConfig();
}

int QConfigJsonObject::GetMuxConfigConcurrency(){
    QJsonObject muxConfig = this->GetMuxConfig();

    if(muxConfig.contains(muxConcurrencyKey))
    {
        QJsonValue config = muxConfig.value(muxConcurrencyKey);
        return config.toInt();
    }
    return DEFAULT_MUX_CONCURRENCY;
}

QConfigJsonObject *QConfigJsonObject::SetMuxConfigConcurrency(int MuxConcurrency){
    QJsonObject muxConfig = this->GetMuxConfig();
    muxConfig.insert(muxConcurrencyKey, MuxConcurrency);
    this->insert(muxKey, muxConfig);
    return this;
}

bool QConfigJsonObject::GetMuxConfigEnabled(){
    QJsonObject muxConfig = this->GetMuxConfig();
    if(muxConfig.contains(muxEnabledKey))
    {
        QJsonValue config = muxConfig.value(muxEnabledKey);
        return config.toBool();
    }
    return DEFAULT_MUX_ENABLED;
}

QConfigJsonObject *QConfigJsonObject::SetMuxConfigEnabled( bool MuxEnabled){
    QJsonObject muxConfig = this->GetMuxConfig();
    muxConfig.insert(muxEnabledKey, MuxEnabled);
    this->insert(muxKey, muxConfig);
    return this;
}

int QConfigJsonObject::GetMuxConfigIdleTimeout(){
    QJsonObject muxConfig = this->GetMuxConfig();
    if(muxConfig.contains(muxIdleTimeoutKey))
    {
        QJsonValue config = muxConfig.value(muxIdleTimeoutKey);
        return config.toInt();
    }
    return DEFAULT_MUX_IDLE_TIME_OUT;
}

QConfigJsonObject *QConfigJsonObject::SetMuxConfigIdleTimeout(int MuxIdleTimeout){
    QJsonObject muxConfig = this->GetMuxConfig();
    muxConfig.insert(muxIdleTimeoutKey, MuxIdleTimeout);
    this->insert(muxKey, muxConfig);
    return this;
}

QJsonObject QConfigJsonObject::GetTCPConfig(){
    if(this->contains(tcpKey))
    {
        QJsonValue config = this->value(tcpKey);
        return config.toObject();
    }
    return QConfigJsonObject::getDefaulTcpObj();
}

bool QConfigJsonObject::GetTCPConfigNoDelay(){
    QJsonObject tcpConfig = this->GetTCPConfig();
    if(tcpConfig.contains(tcpNoDelayKey))
    {
        QJsonValue config = tcpConfig.value(tcpNoDelayKey);
        return config.toBool();
    }
    return DEFAULT_TCP_NO_DELAY;
}

QConfigJsonObject* QConfigJsonObject::SetTCPConfigNoDelay(bool TCPNoDelay){
    QJsonObject tcpConfig = this->GetTCPConfig();
    tcpConfig.insert(tcpNoDelayKey, TCPNoDelay);
    this->insert(tcpKey, tcpConfig);
    return this;
}

bool QConfigJsonObject::GetTCPConfigKeepAlive(){
    QJsonObject tcpConfig = this->GetTCPConfig();
    if(tcpConfig.contains(tcpKeepAliveKey))
    {
        QJsonValue config = tcpConfig.value(tcpKeepAliveKey);
        return config.toBool();
    }
    return DEFAULT_TCP_KEEP_ALIVE;
}


QConfigJsonObject* QConfigJsonObject::SetTCPConfigKeepAlive(bool TCPKeepAlive){
    QJsonObject tcpConfig = this->GetTCPConfig();
    tcpConfig.insert(tcpKeepAliveKey, TCPKeepAlive);
    this->insert(tcpKey, tcpConfig);
    return this;
}


bool QConfigJsonObject::GetTCPConfigPreferIpv4(){
    QJsonObject tcpConfig = this->GetTCPConfig();
    if(tcpConfig.contains(tcpPreferIpv4Key))
    {
        QJsonValue config = tcpConfig.value(tcpPreferIpv4Key);
        return config.toBool();
    }
    return DEFAULT_TCP_PREFER_IPV4;
}

QConfigJsonObject* QConfigJsonObject::SetTCPPreferIpv4(bool TCPPreferIpv4){
    QJsonObject tcpConfig = this->GetTCPConfig();
    tcpConfig.insert(tcpPreferIpv4Key, TCPPreferIpv4);
    this->insert(tcpKey, tcpConfig);
    return this;
}

QJsonObject QConfigJsonObject::GetRouterConfig(){
    if(this->contains(routerKey))
    {
        QJsonValue config = this->value(routerKey);
        return config.toObject();
    }
    return getDefaultRouterObj();
}

bool QConfigJsonObject::GetRouterConfigByPsssEnabled(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerByPassEnableKey))
    {
        QJsonValue config = routerConfig.value(routerByPassEnableKey);
        return config.toBool();
    }
    return DEFAULT_ROUTER_BY_PASS_ENABLED;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigByPsssEnabled(bool RouterByPsssEnabled){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerByPassEnableKey, RouterByPsssEnabled);
    this->insert(routerKey, routerConfig);
    return this;
}

bool QConfigJsonObject::GetRouterConfigProxyEnabled(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerProxyEnableKey))
    {
        QJsonValue config = routerConfig.value(routerProxyEnableKey);
        return config.toBool();
    }
    return DEFAULT_ROUTER_PROXY_ENABLED;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigProxyEnabled(bool RouterProxyEnabled){

    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerProxyEnableKey, RouterProxyEnabled);
    this->insert(routerKey, routerConfig);
    return this;
}

bool QConfigJsonObject::GetRouterConfigBlockEnabled(){
    QJsonObject routerConfig = this->GetRouterConfig();

    if(routerConfig.contains(routerBlockEnableKey))
    {
        QJsonValue config = routerConfig.value(routerBlockEnableKey);
        return config.toBool();
    }
    return DEFAULT_ROUTER_BLOCK_ENABLED;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigBlockEnable(bool RouterBlockEnable){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerBlockEnableKey, RouterBlockEnable);
    this->insert(routerKey, routerConfig);
    return this;
}

QJsonArray QConfigJsonObject::GetRouterConfigByPsssList(){
    QJsonObject routerConfig = this->GetRouterConfig();

    if(routerConfig.contains(routerByPassKey))
    {
        QJsonValue config = routerConfig.value(routerByPassKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();
    return *emptyArray;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigByPsssList(QJsonArray RouterByPsssList){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerByPassKey, RouterByPsssList);
    this->insert(routerKey, routerConfig);
    return this;
}

QJsonArray QConfigJsonObject::GetRouterConfigProxyList(){
    QJsonObject routerConfig = this->GetRouterConfig();

    if(routerConfig.contains(routerProxyKey))
    {
        QJsonValue config = routerConfig.value(routerProxyKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();

    return *emptyArray;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigProxyList(QJsonArray RouterProxyList){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerProxyKey, RouterProxyList);
    this->insert(routerKey, routerConfig);
    return this;
}

QJsonArray QConfigJsonObject::GetRouterConfigBlockList(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerBlockKey))
    {
        QJsonValue config = routerConfig.value(routerBlockKey);
        return config.toArray();
    }
    QJsonArray *emptyArray = new QJsonArray();
    return *emptyArray;
}


QConfigJsonObject* QConfigJsonObject::SetRouterConfigBlockList(QJsonArray RouterBlockList){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerBlockKey, RouterBlockList);
    this->insert(routerKey, routerConfig);
    return this;
}

bool QConfigJsonObject::GetRouterConfigEnabled(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerEnableKey))
    {
        QJsonValue config = routerConfig.value(routerEnableKey);
        return config.toBool();
    }
    return DEFAULT_ROUTER_ENABLED;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigEnabled(bool value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerEnableKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}


QString QConfigJsonObject::GetRouterConfigDefaultPolicy(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerDefaultPolicyKey))
    {
        QJsonValue config = routerConfig.value(routerDefaultPolicyKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_DEFALUT_POLICY;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigDefaultPolicy(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerDefaultPolicyKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}


QString QConfigJsonObject::GetRouterConfigDomainStrategy(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerDomainStrategyKey))
    {
        QJsonValue config = routerConfig.value(routerDomainStrategyKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_DOMAIN_STRATEGY;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigDomainStrategy(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerDomainStrategyKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}

QString QConfigJsonObject::GetRouterConfigGeoip(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerGeoipKey))
    {
        QJsonValue config = routerConfig.value(routerGeoipKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_GEOIP;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigGeoip(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerGeoipKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}

QString QConfigJsonObject::GetRouterConfigGeoipsite(){
    QJsonObject routerConfig = this->GetRouterConfig();
    if(routerConfig.contains(routerGeositeKey))
    {
        QJsonValue config = routerConfig.value(routerGeositeKey);
        return config.toString();
    }
    return DEFAULT_ROUTER_GEOSITE;
}

QConfigJsonObject* QConfigJsonObject::SetRouterConfigGeoipsite(QString value){
    QJsonObject routerConfig = this->GetRouterConfig();
    routerConfig.insert(routerGeositeKey, value);
    this->insert(routerKey, routerConfig);
    return this;
}

QConfigJsonObject::QConnectionConfigListJsonObject QConfigJsonObject::GetConnectionList(){
    if(this->contains(connectionListKey))
    {
        QJsonValue jsonValueList = this->value(connectionListKey);
        QJsonArray newarr = jsonValueList.toArray();
        QConnectionConfigListJsonObject array = static_cast<QConnectionConfigListJsonObject&>(newarr);
        return array;
    }
    return  *(new QConnectionConfigListJsonObject());
}

int QConfigJsonObject::GetLogLevel(){
    if(this->contains(logLevelKey))
    {
        QJsonValue config = this->value(logLevelKey);
        return config.toInt();
    }
    return DEFAULT_LOG_LEVEL;
}

QConfigJsonObject* QConfigJsonObject::SetLogLevel(int value){
    this->insert(logLevelKey, value);
    return this;
}

QString QConfigJsonObject::GetLogFilePath(){
    if(this->contains(logFileKey))
    {
        QJsonValue config = this->value(logFileKey);
        return config.toString();
    }
    return DEFAULT_LOG_FILE_PATH;
}

QConfigJsonObject* QConfigJsonObject::SetLogFilePath(QString path){
    this->insert(logFileKey, path);
    return this;
}

bool QConfigJsonObject::GetDisableHttpCheckKey(){
    if(this->contains(disableHttpCheckKey))
    {
        QJsonValue config = this->value(disableHttpCheckKey);
        return config.toBool();
    }
    return DEFAULT_DISABLE_HTTP_CHECK;
}

QConfigJsonObject* QConfigJsonObject::SetDisableHttpCheckKey(QString val){
    this->insert(logFileKey, val);
    return this;
}


int QConfigJsonObject::GetUDPTimeoutKey(){
    if(this->contains(udpTimeoutKey))
    {
        QJsonValue config = this->value(udpTimeoutKey);
        return config.toInt();
    }
    return DEFAULT_UDP_TIMMEOUT;
}

QConfigJsonObject* QConfigJsonObject::SetUDPTimeoutKey(QString val){
    this->insert(udpTimeoutKey, val);
    return this;
}

QString QConfigJsonObject::GetLocalAddr(){
    if(this->contains(localAddrKey))
    {
        QJsonValue localAddr = this->value(localAddrKey);
        return localAddr.toString();
    }
    return DEFAULT_LOCAL_ADDRESS;
}

QConfigJsonObject* QConfigJsonObject::SetLocalAddr(QString LocalAddr){
    this->insert(localAddrKey, LocalAddr);
    return this;
}

int QConfigJsonObject::GetLocalPort(){
    if(this->contains(localPortKey))
    {
        QJsonValue localPort = this->value(localPortKey);
        return localPort.toInt();
    }
    return DEFAULT_LOCAL_PORT;
}

QConfigJsonObject* QConfigJsonObject::SetLocalPort(int localPort){
    this->insert(localPortKey, localPort);
    return this;
}

//连接配置相关操作
QConfigJsonObject *QConfigJsonObject::AddConnectionConfig(QConnectionConfigJsonObject obj)
{
    QConnectionConfigListJsonObject array = this->GetConnectionList();
    array.append(QJsonValue(obj));
    this->insert(connectionListKey, array);
    return this;
}

QConfigJsonObject *QConfigJsonObject::EditConnectionConfig(int Index, QConnectionConfigJsonObject obj)
{
    QConnectionConfigListJsonObject array = this->GetConnectionList();
    // 这里有两个键单独控制的
    QConnectionConfigJsonObject old = array.At(Index);
    obj.SetLastDelay(old.GetLastDelay())->
            SetLastUseTime(old.GetLastDelay());
    array.replace(Index, QJsonValue(obj));
    this->insert(connectionListKey, array);

    return this;
}

QConfigJsonObject* QConfigJsonObject::DelConnectionConfig(int index)
{
    QConnectionConfigListJsonObject array = this->GetConnectionList();
    array.removeAt(index);
    this->insert(connectionListKey, array);
    return this;
}


QConfigJsonObject* QConfigJsonObject::UpConnectionConfig(int index)
{
    if (index<1) {
        return 0;
    }
    QJsonArray array = this->GetConnectionList();
    QJsonValue nowObj = array.at(index);

    array.replace(index, array.at(index-1));
    array.replace(index-1, nowObj);

    this->insert(connectionListKey, array);

    return this;
}


// 文件操作相关
bool QConfigJsonObject::confirmFile(QString sFile)
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
        QConfigJsonObject obj = GetDefaulObj();
        QJsonDocument *document = new QJsonDocument();
        document->setObject(obj);
        nfile.write(document->toJson());
        nfile.close();
    }
    return true;
}

QConfigJsonObject QConfigJsonObject::GetFromFile(QString sFile)
{

    if (!confirmFile(sFile)) {
        return GetDefaulObj();
    }

    QFile file(sFile);
    file.open(QFileDevice::ReadOnly);
    QString value = file.readAll();

    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8());
    QJsonObject newObject = document.object();
    QConfigJsonObject jsonObject = static_cast<QConfigJsonObject&>(newObject);
    file.close();

    return jsonObject;
}

void QConfigJsonObject::SaveToFile(QString path){
    // 初始化json
    QFile nfile(path);
    nfile.open(QFileDevice::WriteOnly |QFileDevice::Truncate);
    QJsonDocument *document = new QJsonDocument();
    document->setObject(*this);
    nfile.write(document->toJson());
    nfile.close();
}



