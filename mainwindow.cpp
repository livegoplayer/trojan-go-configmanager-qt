#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->advancedSettingsForm = new AdvancedSettingsForm();

    connect(ui->ActionAdd,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->widgetNew->SetFormStatus(0);
            ui->CL->widgetNew->show();
    });

    connect(ui->ActionEdit,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->widgetNew->SetFormStatus(1);
            int rowNum = ui->CL->GetSelectedRowNum();
            if (rowNum == -1) {
                return;
            }

            ui->CL->SetWidgetSelectedLine();
            ui->CL->widgetNew->show();
    });

    connect(ui->ActionDel,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->DelSelectedRow();
    });

    connect(ui->ActionUp,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->UpSelectedRow();
    });


    connect(ui->ActionAdditionalSettings,
            &QAction::triggered,
            this,
            [=] () {
            this->advancedSettingsForm->InitAdvancedSettingFoem();
            this->advancedSettingsForm->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}



