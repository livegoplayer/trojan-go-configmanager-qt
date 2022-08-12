#include "src/ui/advancedsettingsform.h"
#include "ui_advancedsettingsform.h"
#include <QJsonObject>
#include <QJsonArray>
#include <stdlib.h>
#include <stdio.h>
#include <QMessageBox>


AdvancedSettingsForm::AdvancedSettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedSettingsForm)
{
    ui->setupUi(this);
    this->RuleListEditDialog = new RuleListEdit();
    this->EditMuxSettingsForm = new class EditMuxSettingsForm();
    this->EditTcpSettingsForm = new class EditTcpSettingsForm();
    this->setWindowTitle("高级设置");

    connect(ui->ok,  &QPushButton::pressed, this, [=] () {
        this->SaveAdvancedSettingFoem();
        QMessageBox::StandardButton  reply = QMessageBox::question(this, "提示", "更改配置之后需要重启连接方能生效，是否重启？",
                                    QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            emit this->requestReconnect();
        }
    });

    connect(ui->cancel,  &QPushButton::pressed, this, [=] () {
        this->hide();
    });

    connect(ui->by_pass_edit,  &QPushButton::pressed, this, [=] () {
        this->RuleListEditDialog->InitByType(RuleListEdit::BY_PASS_RULE_FORM);
        this->RuleListEditDialog->show();
    });
    connect(ui->proxy_edit,  &QPushButton::pressed, this, [=] () {
        this->RuleListEditDialog->InitByType(RuleListEdit::PROXY_RULE_FORM);
        this->RuleListEditDialog->show();
    });
    connect(ui->block_edit,  &QPushButton::pressed, this, [=] () {
        this->RuleListEditDialog->InitByType(RuleListEdit::BLOCK_RULE_FORM);
        this->RuleListEditDialog->show();
    });

    connect(ui->mux_edit,  &QPushButton::pressed, this, [=] () {
        this->EditMuxSettingsForm->InitMuxConfigs();
        this->EditMuxSettingsForm->show();
    });

    connect(ui->tcp_edit,  &QPushButton::pressed, this, [=] () {
        this->EditTcpSettingsForm->InitTCPConfigs();
        this->EditTcpSettingsForm->show();
    });
}

AdvancedSettingsForm::~AdvancedSettingsForm()
{
    delete ui;
}

void AdvancedSettingsForm::InitAdvancedSettingFoem() {
    QConfigJsonObject configs = ConfigManager::GetConfigs();
    QString localAddr = configs.GetLocalAddr();
    int localPort = configs.GetLocalPort();
    int LogLevel = configs.GetLogLevel();

    bool muxEnabled = configs.GetMuxConfigEnabled();

    bool routerByPassEnabe = configs.GetRouterConfigByPsssEnabled();
    bool routerProxyEnabe = configs.GetRouterConfigProxyEnabled();
    bool routerBlockEnabe = configs.GetRouterConfigBlockEnabled();

    // 填充
    char portText[10] = {0};
    ui->log_level->setCurrentIndex(LogLevel);
    ui->local_addr->setText(localAddr);
    ui->local_port->setText(itoa(localPort, portText, 10));
    ui->by_pass_check_box->setChecked(routerByPassEnabe);
    ui->proxy_check_box->setChecked(routerProxyEnabe);
    ui->block_check_box->setChecked(routerBlockEnabe);
    ui->mux_check_box->setChecked(muxEnabled);
}

void AdvancedSettingsForm::SaveAdvancedSettingFoem()
{
    int LogLevel = ui->log_level->currentIndex();
    QString localAddr = ui->local_addr->text();
    int localPort = ui->local_port->text().toInt();
    bool muxEnabled =  ui->mux_check_box->isChecked();
    bool routerByPassEnabe = ui->by_pass_check_box->isChecked();
    bool routerProxyEnabe = ui->proxy_check_box->isChecked();
    bool routerBlockEnabe = ui->block_check_box->isChecked();

    QConfigJsonObject configs = ConfigManager::GetConfigs();

    configs.SetLogLevel(LogLevel)->SetLocalAddr(localAddr)->
            SetLocalPort(localPort)->
            SetMuxConfigEnabled(muxEnabled)->
            SetRouterConfigByPsssEnabled(routerByPassEnabe)->
            SetRouterConfigProxyEnabled(routerProxyEnabe)->
            SetRouterConfigBlockEnable(routerBlockEnabe);
    ConfigManager::SaveConfig(configs);

    this->hide();
}



