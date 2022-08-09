#ifndef QTHEMECONFIG_H
#define QTHEMECONFIG_H

#include "src/config/configmanager.h"
#include <QObject>

class QThemeConfig : public QObject
{
    Q_OBJECT
public:
    explicit QThemeConfig(QObject *parent = nullptr);

    void registerListen();
    bool isDarkTheme();
    void setupTheme();
    void setupThemeOnChange(int index);
    void applyLightPalette();
    void applyLightQss();
    void applyDarkPalette();
    void applyDarkQss();

    ConfigManager *ConfigManager;
    bool isLightTheme();
    void setTheme(int theme);
    void updateTheme();
signals:

};

#endif // QTHEMECONFIG_H
