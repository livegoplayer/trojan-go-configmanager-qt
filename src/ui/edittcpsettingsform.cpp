#include "src/ui/edittcpsettingsform.h"
#include "src/config/qconfigjsonobject.h"
#include "ui_edittcpsettingsform.h"

EditTcpSettingsForm::EditTcpSettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTcpSettingsForm)
{
    ui->setupUi(this);
    this->ConfigManager = new class ConfigManager();

    this->InitTCPConfigs();
    connect(ui->ok, &QPushButton::pressed, this, [=] () {
        this->SaveTCPConfigs();
        this->hide();
    });

    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });

    connect(ui->reset, &QPushButton::pressed, this, [=] () {
        this->ResetTCPSettingsForm();
    });
}

EditTcpSettingsForm::~EditTcpSettingsForm()
{
    delete ui;
}

void EditTcpSettingsForm::SaveTCPConfigs() {
    bool no_delay = ui->no_delay->isChecked();
    bool keep_alive = ui->keep_alive->isChecked();
    bool prefer_ipv4 = ui->prefer_ipv4->isChecked();
    QConfigJsonObject config = this->ConfigManager->GetConfigs();
    config.SetTCPConfigNoDelay(no_delay);
    config.SetTCPConfigKeepAlive(keep_alive);
    config.SetTCPPreferIpv4(prefer_ipv4);

    this->ConfigManager->SaveConfig(config);
}

void EditTcpSettingsForm::InitTCPConfigs() {
    QConfigJsonObject config = this->ConfigManager->GetConfigs();
    bool no_delay = config.GetTCPConfigNoDelay();
    bool keep_alive = config.GetTCPConfigKeepAlive();
    bool prefer_ipv4 = config.GetTCPConfigPreferIpv4();

    ui->no_delay->setChecked(no_delay);
    ui->keep_alive->setChecked(keep_alive);
    ui->prefer_ipv4->setChecked(prefer_ipv4);
}

void EditTcpSettingsForm::ResetTCPSettingsForm(){
    ui->no_delay->setChecked(QConfigJsonObject::DEFAULT_TCP_NO_DELAY);
    ui->keep_alive->setChecked(QConfigJsonObject::DEFAULT_TCP_KEEP_ALIVE);
    ui->prefer_ipv4->setChecked(QConfigJsonObject::DEFAULT_TCP_PREFER_IPV4);
}

