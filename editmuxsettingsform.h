#ifndef EDITMUXSETTINGSFORM_H
#define EDITMUXSETTINGSFORM_H

#include "ConfigManager.h"

#include <QDialog>

namespace Ui {
class EditMuxSettingsForm;
}

class EditMuxSettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditMuxSettingsForm(QWidget *parent = nullptr);
    ~EditMuxSettingsForm();
    // 配置管理组件
    ConfigManager *ConfigManager;
    void InitMuxConfigs();
    void SaveMuxConfigs();
    void ResetMuxSettingsForm();
private:
    Ui::EditMuxSettingsForm *ui;
};

#endif // EDITMUXSETTINGSFORM_H
