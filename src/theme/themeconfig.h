#ifndef THEMECONFIG_H
#define THEMECONFIG_H

#include <QObject>

class ThemeConfig : public QObject
{
    Q_OBJECT
public:
    explicit ThemeConfig(QObject *parent = nullptr);

    static bool isSystemDarkTheme();

    static void registerListen();
    static void setupTheme();
    static void setupThemeOnChange(int);

    static void applyLightPalette();
    static void applyDarkPalette();

    static void applyLightQss();
    static void applyDarkQss();
signals:

};

#endif // THEMECONFIG_H
