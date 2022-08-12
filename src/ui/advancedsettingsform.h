#ifndef ADVANCEDSETTINGSFORM_H
#define ADVANCEDSETTINGSFORM_H

#include <QDialog>
#include "src/config/configmanager.h"
#include "src/ui/editmuxsettingsform.h"
#include "src/ui/edittcpsettingsform.h"
#include "src/ui/rulelistedit.h"
namespace Ui {
class AdvancedSettingsForm;
}

class AdvancedSettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedSettingsForm(QWidget *parent = nullptr);
    ~AdvancedSettingsForm();
    // 编辑规则的组件
    RuleListEdit *RuleListEditDialog;
    // 编辑mux配置的组件
    EditMuxSettingsForm *EditMuxSettingsForm;
    // 编辑tcp配置的组件
    EditTcpSettingsForm *EditTcpSettingsForm;

    void InitAdvancedSettingFoem();
    void SaveAdvancedSettingFoem();
    void InitRuleEditFoemByType(int type);
private:
    Ui::AdvancedSettingsForm *ui;
signals:
    void requestReconnect();
};

#endif // ADVANCEDSETTINGSFORM_H
