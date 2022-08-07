#include "additemdialog.h"
#include "ui_additemdialog.h"

AddItemDialog::AddItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);

    connect(ui->ok, &QPushButton::pressed, this, [=] () {
        this->AddOver();
    });


    connect(ui->cancel, &QPushButton::pressed, this, [=] () {
        this->hide();
    });
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void AddItemDialog::AddOver() {
    QString text = ui->lineEdit->text();
    emit this->AddSignal(text);
    this->hide();
    ui->lineEdit->setText("");
}

