#include "src/ui/connectionform.h"
#include "src/config/qconfigjsonobject.h"
#include "ui_connectionform.h"

#include <QFileDialog>

ConnectionForm::ConnectionForm(QWidget *parent, int status) :
    QDialog(parent),
    ui(new Ui::ConnectionForm)
{
    ui->setupUi(this);

    this->SetFormStatus(status);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });

    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });

    connect(ui->ssl_settings_show, &QCheckBox::stateChanged, this, [=] (int status) {
        if (status == 0) {
            this->HideSSLSettings();
        }else{
            this->ShowSSLSettings();
        }
    });
    this->AddItemDialog = new class AddItemDialog();
    connect(ui->add_alpn_item, &QPushButton::pressed, this, [=] () {
        this->AddItemDialog->show();
    });

    connect(ui->del_alpn_item, &QPushButton::pressed, this, [=] () {
        ui->alpn_list->takeItem(ui->alpn_list->currentRow());
    });

    connect(this->AddItemDialog, &AddItemDialog::AddSignal, this, &ConnectionForm::AddNewItem);

    connect(ui->resetSSL,  &QPushButton::pressed, this, [=] () {
        this->ResetSSLSettings();
    });

    connect(ui->cert_file_open,  &QPushButton::pressed, this, [=] () {
        QString path = QFileDialog::getOpenFileName(this, "选择文件", QDir::currentPath());
        if (!path.isEmpty()){
            ui->cert->setText(path);
        }
    });

    ui->ssl_settings_show->setChecked(false);
    this->HideSSLSettings();
}

ConnectionForm::~ConnectionForm()
{
    delete ui;
}

void ConnectionForm::SetFormStatus(int status) {
    this->status = status;
    switch (status) {
        case 0:
            this->setWindowTitle("新建");
            this->ResetSSLSettings();
            break;
        case 1:
            this->setWindowTitle("编辑");
            break;
        default:
            this->setWindowTitle("新建");
            this->ResetSSLSettings();

            break;
    }
}

void ConnectionForm::ShowInWiget(QLayout *widget) {
    for (int i = 0; i < widget->layout()->count(); ++i) {
            QWidget* w = widget->layout()->itemAt(i)->widget();
            if (w != NULL)
                w->show();
    }
}

void ConnectionForm::HideInWiget(QLayout *widget) {
    for (int i = 0; i < widget->count(); ++i) {
            QWidget* w = widget->itemAt(i)->widget();
            if (w != NULL)
                w->hide();
    }
}


void ConnectionForm::ShowSSLSettings() {
    this->ShowInWiget(ui->ssl_settings_form1);
    this->ShowInWiget(ui->ssl_settings_form2);
    this->ShowInWiget(ui->ssl_settings_form3);
    this->ShowInWiget(ui->ssl_settings_form4);
}

void ConnectionForm::HideSSLSettings() {
    this->HideInWiget(ui->ssl_settings_form1);
    this->HideInWiget(ui->ssl_settings_form2);
    this->HideInWiget(ui->ssl_settings_form3);
    this->HideInWiget(ui->ssl_settings_form4);
}

int ConnectionForm::GetFormStatus() {
    return this->status;
}

void ConnectionForm::SetItemIndex(int index) {
    this->itemIndex = index;
}

int ConnectionForm::GetItemIndex() {
    return this->itemIndex;
}

void ConnectionForm::ResetSSLSettings() {
    QConfigJsonObject::QConnectionConfigJsonObject *obj = new QConfigJsonObject::QConnectionConfigJsonObject();

    ui->verify->setChecked(obj->GetSSLConfigVerify());
    ui->verify_hostname->setChecked(obj->GetSSLConfigVerifyHostname());
    ui->prefer_server_cipher->setChecked(obj->GetSSLConfigPreferServerCipher());
    ui->session_ticket->setChecked(obj->GetSSLConfigSessionTicket());
    ui->reuse_session->setChecked(obj->GetSSLConfigReuseSession());

    ui->sni->setText(obj->GetSSLConfigSni());
    ui->cert->setText(obj->GetSSLConfigCert());
    ui->key->setText(obj->GetSSLConfigKey());
    ui->key_password->setText(obj->GetSSLConfigKeyPassword());
    ui->cipher->setText(obj->GetSSLConfigCipher());
    ui->curves->setText(obj->GetSSLConfigCurves());
    ui->plain_http_response->setText(obj->GetSSLPlainHttpResponse());
    ui->fingerprint->setText(obj->GetSSLConfigFingerprint());

    QJsonArray array = obj->GetSSLConfigAlpn();
    ui->alpn_list->clear();
    for (int i=0; i < array.count(); i++) {
        QString item = array.at(i).toString();
        ui->alpn_list->addItem(item);
    }
}

QConfigJsonObject::QConnectionConfigJsonObject ConnectionForm::GetFormSettings() {
    QConfigJsonObject::QConnectionConfigJsonObject *obj = new QConfigJsonObject::QConnectionConfigJsonObject();
    QJsonArray *array = new QJsonArray();
    for (int i=0; i < ui->alpn_list->count(); i++) {
        QString item = ui->alpn_list->item(i)->text();
        array->append(item);
    }
    obj->SetName(ui->name->text())->
            SetServerAddr(ui->addr->text())->
            SetServerPort(ui->port->text().toInt())->
            SetPassword(ui->password->text())->
            SetSSLConfigVerify(ui->verify->isChecked())->
            SetSSLConfigVerifyHostname(ui->verify_hostname->isChecked())->
            SetSSLConfigPreferServerCipher(ui->prefer_server_cipher->isChecked())->
            SetSSLConfigSessionTicket(ui->session_ticket->isChecked())->
            SetSSLConfigReuseSession(ui->reuse_session->isChecked())->
            SetSSLConfigSni(ui->sni->text())->
            SetSSLConfigCert(ui->cert->text())->
            SetSSLConfigKey(ui->key->text())->
            SetSSLConfigKeyPassword(ui->key_password->text())->
            SetSSLConfigCipher(ui->cipher->text())->
            SetSSLConfigCurves(ui->curves->text())->
            SetSSLConfigPlainHttpResponse(ui->plain_http_response->text())->
            SetSSLConfigFingerprint(ui->fingerprint->text())->
            SetSSLConfigAlpn(*array);

    return *obj;
}


void ConnectionForm::SetSettings(QConfigJsonObject::QConnectionConfigJsonObject *obj) {
    char portText[10] = {0};
    ui->name->setText(obj->GetName());
    ui->addr->setText(obj->GetServerAddr());
    ui->port->setText(itoa(obj->GetServerPort(), portText, 10));
    ui->password->setText(obj->GetPassword());

    ui->verify->setChecked(obj->GetSSLConfigVerify());
    ui->verify_hostname->setChecked(obj->GetSSLConfigVerifyHostname());
    ui->prefer_server_cipher->setChecked(obj->GetSSLConfigPreferServerCipher());
    ui->session_ticket->setChecked(obj->GetSSLConfigSessionTicket());
    ui->reuse_session->setChecked(obj->GetSSLConfigReuseSession());

    ui->sni->setText(obj->GetSSLConfigSni());
    ui->cert->setText(obj->GetSSLConfigCert());
    ui->key->setText(obj->GetSSLConfigKey());
    ui->key_password->setText(obj->GetSSLConfigKeyPassword());
    ui->cipher->setText(obj->GetSSLConfigCipher());
    ui->curves->setText(obj->GetSSLConfigCurves());
    ui->plain_http_response->setText(obj->GetSSLPlainHttpResponse());
    ui->fingerprint->setText(obj->GetSSLConfigFingerprint());

    QJsonArray array = obj->GetSSLConfigAlpn();
    ui->alpn_list->clear();
    for (int i=0; i < array.count(); i++) {
        QString item = array.at(i).toString();
        ui->alpn_list->addItem(item);
    }
}

void ConnectionForm::AddNewItem(QString text) {
    if (!this->isHidden()){
        ui->alpn_list->addItem(text);
    }
}



