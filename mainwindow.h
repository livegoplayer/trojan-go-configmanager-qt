#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "advancedsettingsform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int AddConnection();
    int RefleshConnectionList();
private:
    Ui::MainWindow *ui;
    bool confirmFile(QString path);

    AdvancedSettingsForm *advancedSettingsForm;
};
#endif // MAINWINDOW_H;
