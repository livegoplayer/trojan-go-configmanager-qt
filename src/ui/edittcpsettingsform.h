#ifndef EDITTCPSETTINGSFORM_H
#define EDITTCPSETTINGSFORM_H

#include "src/config/configmanager.h"
#include <QDialog>

namespace Ui {
class EditTcpSettingsForm;
}

class EditTcpSettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditTcpSettingsForm(QWidget *parent = nullptr);
    ~EditTcpSettingsForm();

    void SaveTCPConfigs();
    void InitTCPConfigs();
    void ResetTCPSettingsForm();
private:
    Ui::EditTcpSettingsForm *ui;
};

#endif // EDITTCPSETTINGSFORM_H
