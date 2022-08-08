#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->advancedSettingsForm = new AdvancedSettingsForm();
    this->TrojanGoManger = new class TrojanGoManger();

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

    connect(ui->ActionConnect,
            &QAction::triggered,
            this,
            [=] () {
            ui->CL->ConfigManager->CreateClientConfigByItemIndex(0);
            this->TrojanGoManger->start();
    });

    connect(ui->ActionDisconnect,
            &QAction::triggered,
            this,
            [=] () {
            this->TrojanGoManger->Disconnet();
            this->TrojanGoManger->quit();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}



