#ifndef TCPCONFIGEDIT_H
#define TCPCONFIGEDIT_H

#include "configmanager.h"
#include <QDialog>

namespace Ui {
class TcpConfigEdit;
}

class TcpConfigEdit : public QDialog
{
    Q_OBJECT

public:
    explicit TcpConfigEdit(QWidget *parent = nullptr);
    ~TcpConfigEdit();

    ConfigManager *ConfigManager;
    void InitTCPConfigs();
    void SaveTCPConfigs();
private:
    Ui::TcpConfigEdit *ui;
};

#endif // TCPCONFIGEDIT_H
