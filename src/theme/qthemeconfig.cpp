#include "src/theme/qthemeconfig.h"

#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QPalette>
#include <QStyle>
#include <QStyleFactory>


// copy from trojan-qt5 本人是后端程序员，不擅长调样式
QThemeConfig::QThemeConfig(QObject *parent)
    : QObject{parent}
{
    this->ConfigManager = new class ConfigManager();
    this->updateTheme();
}

bool QThemeConfig::isDarkTheme()
{
    return this->ConfigManager->GetConfigs().GetTheme() == QConfigJsonObject::THEME_DARK;
}


bool QThemeConfig::isLightTheme()
{
    return this->ConfigManager->GetConfigs().GetTheme() == QConfigJsonObject::THEME_LIGHT;
}


void QThemeConfig::setTheme(int theme)
{
    if (isLightTheme() && theme == QConfigJsonObject::THEME_DARK) {
        applyDarkPalette();
        applyDarkQss();
    }
    if (isDarkTheme() && theme == QConfigJsonObject::THEME_LIGHT) {
        applyLightPalette();
        applyLightQss();
    }
}

void QThemeConfig::updateTheme()
{
    if (isDarkTheme()) {
        applyDarkPalette();
        applyDarkQss();
    }
    if (isLightTheme()) {
        applyLightPalette();
        applyLightQss();
    }
}

void QThemeConfig::applyLightPalette()
{
    qApp->setPalette(QStyleFactory::create("Fusion")->standardPalette());
}

void QThemeConfig::applyLightQss()
{
    QFile qssFile(":/qss/light.qss");
    qssFile.open(QIODevice::ReadOnly | QIODevice::Text);
    qApp->setStyleSheet(qssFile.readAll());
}

void QThemeConfig::applyDarkPalette()
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127,127,127));
    darkPalette.setColor(QPalette::Base, QColor(42,42,42));
    darkPalette.setColor(QPalette::AlternateBase, QColor(66,66,66));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127,127,127));
    darkPalette.setColor(QPalette::Dark, QColor(35,35,35));
    darkPalette.setColor(QPalette::Shadow, QColor(20,20,20));
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127,127,127));
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42,130,218));
    darkPalette.setColor(QPalette::Highlight, QColor(42,130,218));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80,80,80));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127,127,127));
    qApp->setPalette(darkPalette);
}

void QThemeConfig::applyDarkQss()
{
    QFile qssFile(":/qss/dark.qss");
    qssFile.open(QIODevice::ReadOnly | QIODevice::Text);
    qApp->setStyleSheet(qssFile.readAll());
}
