#ifndef CONNECTIONFORM_H
#define CONNECTIONFORM_H

#include "src/ui/additemdialog.h"
#include "src/config/qconfigjsonobject.h"

#include <QDialog>

namespace Ui {
class ConnectionForm;
}


class ConnectionForm : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionForm(QWidget *parent, int status);
    ~ConnectionForm();
    QString GetFormText(QString name);
    void SetFormStatus(int status);
    int GetFormStatus();

    int itemIndex = -1;
    void SetItemIndex(int index);
    void SetFormText(QString name, QString value);
    int GetItemIndex();

    static const int STATUS_NEW = 0;
    static const int STATUS_EDIT =  1;

//    // 以下的key归属于connectionListKey
//    constexpr static const char connectionItemNameKey[] = "name";
//    constexpr static const char connectionItemServerAddrKey[] = "server_addr";
//    constexpr static const char connectionItemServerPortKey[] = "server_port";
//    constexpr static const char connectionItemPasswordKey[] = "password";
//    constexpr static const char connectionItemLastDelayKey[] = "last_delay_time";
//    constexpr static const char connectionItemLastUseTimeKey[] = "last_use_time";
//    constexpr static const char connectionItemVerifyKey[] = "verify";
//    constexpr static const char connectionItemVerifyHomenameKey[] = "verify_hostname";
//    constexpr static const char connectionItemPreferServerCipherKey[] = "prefer_server_cipher";
//    constexpr static const char connectionItemSessionTicketKey[] = "session_ticket";
//    constexpr static const char connectionItemReuseSessionKey[] = "reuse_session";
//    constexpr static const char connectionItemSniKey[] = "sni";
//    constexpr static const char connectionItemCertKey[] = "cert";
//    constexpr static const char connectionItemKeyKey[] = "key";
//    constexpr static const char connectionItemKeyPasswordKey[] = "key_password";
//    constexpr static const char connectionItemCipherKey[] = "cipher";
//    constexpr static const char connectionItemCurvesKey[] = "curves";
//    constexpr static const char connectionItemPlainHttpResponseKey[] = "plain_http_response";
//    constexpr static const char connectionItemFingerprintKey[] = "fingerprint";
//    constexpr static const char connectionItemAlpnKey[] = "alpn";
    AddItemDialog *AddItemDialog;
    void HideInWiget(QLayout *widget);
    void ShowInWiget(QLayout *widget);
    void ShowSSLSettings();
    void HideSSLSettings();
    void ResetSSLSettings();
    QConfigJsonObject::QConnectionConfigJsonObject GetFormSettings();
    void SetSettings(QConfigJsonObject::QConnectionConfigJsonObject *obj);
private:
    int status = 0;
    Ui::ConnectionForm *ui;

public slots:
    void AddNewItem(QString text);
};

#endif // CONNECTIONFORM_H
