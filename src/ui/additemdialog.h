#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemDialog(QWidget *parent = nullptr);
    ~AddItemDialog();

    void AddOver();
private:
    Ui::AddItemDialog *ui;

signals:
    void AddSignal(QString text);
};

#endif // ADDITEMDIALOG_H
