#ifndef CONNECTIONFORM_H
#define CONNECTIONFORM_H

#include "src/ui/additemdialog.h"
#include "src/config/qconfigjsonobject.h"

#include <QDialog>

namespace Ui {
class ConnectionForm;
}


class ConnectionForm : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionForm(QWidget *parent, int status);
    ~ConnectionForm();
    QString GetFormText(QString name);
    void SetFormStatus(int status);
    int GetFormStatus();

    int itemIndex = -1;
    void SetItemIndex(int index);
    void SetFormText(QString name, QString value);
    int GetItemIndex();

    static const int STATUS_NEW = 0;
    static const int STATUS_EDIT =  1;

    AddItemDialog *AddItemDialog;
    void HideInWiget(QLayout *widget);
    void ShowInWiget(QLayout *widget);
    void ShowSSLSettings();
    void HideSSLSettings();
    void ResetSSLSettings();
    QConfigJsonObject::QConnectionConfigJsonObject GetFormSettings();
    void SetSettings(QConfigJsonObject::QConnectionConfigJsonObject *obj);
private:
    int status = 0;
    Ui::ConnectionForm *ui;

public slots:
    void AddNewItem(QString text);
};

#endif // CONNECTIONFORM_H
