#include "rulelistedit.h"
#include "ui_rulelistedit.h"
#include <QJsonArray>

RuleListEdit::RuleListEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleListEdit)
{
    ui->setupUi(this);
    this->ConfigManager = new class ConfigManager();
    this->AddItemDialog = new class AddItemDialog();

    connect(ui->add, &QPushButton::pressed, this, [=] () {
        this->AddItemDialog->show();
    });

    connect(ui->del, &QPushButton::pressed, this, [=] () {
        this->DelSelctedItem();
    });

    connect(ui->ok, &QPushButton::pressed, this, [=] () {
        this->SaveRuleListByType();
        this->hide();
    });

    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });

    connect(this->AddItemDialog, &AddItemDialog::AddSignal, this, &RuleListEdit::AddNewItem);
}

RuleListEdit::~RuleListEdit()
{
    delete ui;
}

int RuleListEdit::GetType()
{
    return this->type;
}

void RuleListEdit::SetType(int type)
{
    this->type = type;
}

void RuleListEdit::InitByType(int type)
{
    QConfigJsonObject config = this->ConfigManager->GetConfigs();
    QJsonArray array;
    QString label;
    this->SetType(type);
    switch (type) {
    case RuleListEdit::BY_PASS_RULE_FORM:
        array = config.GetRouterConfigByPsssList();
        label = "直连列表";
        break;
    case RuleListEdit::PROXY_RULE_FORM:
        array = config.GetRouterConfigProxyList();
        label = "强制代理列表";
        break;
    case RuleListEdit::BLOCK_RULE_FORM:
        array = config.GetRouterConfigBlockList();
        label = "屏蔽列表";
        break;
    default:
        break;
    }

    ui->list->clear();
    for (int i=0; i < array.count(); i++) {
        QString item = array.at(i).toString();
        ui->list->addItem(item);
    }

    ui->label->setText(label);
    this->setWindowTitle( "编辑" + label);
}

void RuleListEdit::SaveRuleListByType() {
    QJsonArray *array = new QJsonArray();
    for (int i=0; i < ui->list->count(); i++) {
        QString item = ui->list->item(i)->text();
        array->append(item);
    }
    QConfigJsonObject config = this->ConfigManager->GetConfigs();
    switch (this->type) {
    case RuleListEdit::BY_PASS_RULE_FORM:
        config.SetRouterConfigByPsssList(*array);
        break;
    case RuleListEdit::PROXY_RULE_FORM:
        config.SetRouterConfigProxyList(*array);
        break;
    case RuleListEdit::BLOCK_RULE_FORM:
        config.SetRouterConfigBlockList(*array);
        break;
    default:
        config.SetRouterConfigByPsssList(*array);
        break;
    }

    this->ConfigManager->SaveConfig(config);
}

void RuleListEdit::AddItem(QString text) {
    ui->list->addItem(text);
}

void RuleListEdit::AddNewItem(QString text) {
    if (!this->isHidden()){
        this->AddItem(text);
    }
}

void RuleListEdit::DelSelctedItem() {
    ui->list->takeItem(ui->list->currentRow());
}

