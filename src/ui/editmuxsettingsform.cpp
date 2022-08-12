#include "src/ui/editmuxsettingsform.h"
#include "ui_editmuxsettingsform.h"

EditMuxSettingsForm::EditMuxSettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMuxSettingsForm)
{

    ui->setupUi(this);

    this->InitMuxConfigs();
    connect(ui->ok, &QPushButton::pressed, this, [=] () {
        this->SaveMuxConfigs();
        this->hide();
    });


    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });

    connect(ui->reset, &QPushButton::pressed, this, [=] () {
        this->ResetMuxSettingsForm();
    });
}

EditMuxSettingsForm::~EditMuxSettingsForm()
{
    delete ui;
}

void EditMuxSettingsForm::SaveMuxConfigs() {
    int concurrency = ui->concurrency->value();
    int idle_timeout = ui->idle_timeout->value();
    QConfigJsonObject config = ConfigManager::GetConfigs();
    config.SetMuxConfigConcurrency(concurrency);
    config.SetMuxConfigIdleTimeout(idle_timeout);
    ConfigManager::SaveConfig(config);
}

void EditMuxSettingsForm::InitMuxConfigs() {
    QConfigJsonObject config = ConfigManager::GetConfigs();
    int concurrency = config.GetMuxConfigConcurrency();
    int idle_timeout = config.GetMuxConfigIdleTimeout();
    ui->concurrency->setValue(concurrency);
    ui->idle_timeout->setValue(idle_timeout);
}

void EditMuxSettingsForm::ResetMuxSettingsForm(){
    ui->concurrency->setValue(QConfigJsonObject::DEFAULT_MUX_CONCURRENCY);
    ui->idle_timeout->setValue(QConfigJsonObject::DEFAULT_MUX_IDLE_TIME_OUT);
}
