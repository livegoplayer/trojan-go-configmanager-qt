#include "tcpconfigedit.h"
#include "ui_tcpconfigedit.h"

TcpConfigEdit::TcpConfigEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpConfigEdit)
{
    ui->setupUi(this);

    ui->setupUi(this);
    this->ConfigManager = new class ConfigManager();

    this->InitTCPConfigs();
    connect(ui->ok, &QPushButton::pressed, this, [=] () {
        this->SaveTCPConfigs();
    });

    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });
}

TcpConfigEdit::~TcpConfigEdit()
{
    delete ui;
}

void TcpConfigEdit::SaveTCPConfigs() {
    bool no_delay = ui->no_delay->isChecked();
    bool keep_alive = ui->keep_alive->isChecked();
    bool prefer_ipv4 = ui->prefer_ipv4->isChecked();

    QConfigJsonObject config = this->ConfigManager->GetConfigs();
    config.SetTCPConfigNoDelay(no_delay);
    config.SetTCPConfigKeepAlive(keep_alive);
    config.SetTCPConfigKeepAlive(prefer_ipv4);

    this->ConfigManager->SaveConfig(config);
}

void TcpConfigEdit::InitTCPConfigs() {
    QConfigJsonObject config = this->ConfigManager->GetConfigs();
    bool no_delay = config.GetTCPConfigNoDelay();
    bool keep_alive = config.GetTCPConfigKeepAlive();
    bool prefer_ipv4 = config.GetTCPConfigPreferIpv4();
    ui->no_delay->setChecked(no_delay);
    ui->keep_alive->setChecked(keep_alive);
    ui->prefer_ipv4->setChecked(prefer_ipv4);
}
