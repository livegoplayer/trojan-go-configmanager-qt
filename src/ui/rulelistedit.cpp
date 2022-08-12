#include "src/ui/rulelistedit.h"
#include "ui_rulelistedit.h"
#include <QJsonArray>

RuleListEdit::RuleListEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleListEdit)
{
    ui->setupUi(this);
    this->AddItemDialog = new class AddItemDialog();

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

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

    // 助手
    connect(ui->category_ads, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::category_ads);
    });

    connect(ui->category_ads_all, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::category_ads_all);
    });

    connect(ui->tld_cn, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::tld_cn);
    });

    connect(ui->notld_cn, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::notld_cn);
    });

    connect(ui->geolocation_cn, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::geolocation_cn);
    });

    connect(ui->nogeolocation_cn, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::nogeolocation_cn);
    });

    connect(ui->cn, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::cn);
    });

    connect(ui->Apple, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::apple);
    });

    connect(ui->Google, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::google);
    });

    connect(ui->Microsoft, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::microsoft);
    });

    connect(ui->Facebook, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::facebook);
    });

    connect(ui->Twitter, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::twitter);
    });

    connect(ui->Telegram, &QPushButton::pressed, this, [=] () {
        this->AddItem(RuleListEdit::telegram);
    });

    connect(ui->addHelper, &QCheckBox::stateChanged, this, [=] (int status) {
        if (status == 0) {
            this->HideHelper();
        }else{
            this->ShowHelper();
        }
    });

    connect(ui->diyAddHelper, &QCheckBox::stateChanged, this, [=] (int status) {
        if (status == 0) {
            this->HideDiyHelper();
        }else{
            this->ShowDiyHelper();
        }
    });

    this->HideDiyHelper();
    this->HideHelper();
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
    QConfigJsonObject config = ConfigManager::GetConfigs();
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
    QConfigJsonObject config = ConfigManager::GetConfigs();
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

    ConfigManager::SaveConfig(config);
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


void RuleListEdit::ShowInWiget(QLayout *widget) {
    for (int i = 0; i < widget->layout()->count(); ++i) {
            QWidget* w = widget->layout()->itemAt(i)->widget();
            if (w != NULL)
                w->show();
    }
}

void RuleListEdit::HideInWiget(QLayout *widget) {
    for (int i = 0; i < widget->count(); ++i) {
            QWidget* w = widget->itemAt(i)->widget();
            if (w != NULL)
                w->hide();
    }
}

void RuleListEdit::HideHelper() {
    this->HideInWiget(ui->adds->layout());
    this->HideInWiget(ui->china->layout());
    this->HideInWiget(ui->no_china->layout());
    this->HideInWiget(ui->always_use->layout());
//    this->HideInWiget(ui->diyAddHelper->layout());
}

void RuleListEdit::HideDiyHelper() {
    this->HideInWiget(ui->textdiyhelper->layout());
}

void RuleListEdit::ShowHelper() {
    this->ShowInWiget(ui->adds->layout());
    this->ShowInWiget(ui->china->layout());
    this->ShowInWiget(ui->no_china->layout());
    this->ShowInWiget(ui->always_use->layout());
//    this->ShowInWiget(ui->diyAddHelper->layout());
}

void RuleListEdit::ShowDiyHelper() {
    this->ShowInWiget(ui->textdiyhelper->layout());
}



