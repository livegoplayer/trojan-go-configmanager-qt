#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/theme/qthemeconfig.h"
#include "src/ui/advancedsettingsform.h"
#include <QSystemTrayIcon>
#include "src/trojan/trojangomanger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSystemTrayIcon *QSystemTrayIcon;
    QThemeConfig *QThemeConfig;


    // 惟独这一个action不能出现在ui中
    QAction *showAction;
    QAction *minAction;
    QAction *maxAction;

    int AddConnection();
    int RefleshConnectionList();
    void InitQuitAction(QApplication *a);
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::MainWindow *ui;
    bool confirmFile(QString path);

    AdvancedSettingsForm *advancedSettingsForm;
};
#endif // MAINWINDOW_H;
