#ifndef RULELISTEDIT_H
#define RULELISTEDIT_H

#include "additemdialog.h"
#include "configmanager.h"

#include <QDialog>

namespace Ui {
class RuleListEdit;
}

class RuleListEdit : public QDialog
{
    Q_OBJECT

public:
    explicit RuleListEdit(QWidget *parent = nullptr);
    ~RuleListEdit();

    int GetType();
    void SetType(int type);

    static int const BY_PASS_RULE_FORM = 0;
    static int const PROXY_RULE_FORM = 1;
    static int const BLOCK_RULE_FORM = 2;

    ConfigManager *ConfigManager;
    AddItemDialog *AddItemDialog;

    void InitByType(int type);
    void SaveRuleListByType();
    void AddItem(QString text);
    void DelSelctedItem();
private:
    Ui::RuleListEdit *ui;

    int type;

public slots:
    void AddNewItem(QString text);
};

#endif // RULELISTEDIT_H
