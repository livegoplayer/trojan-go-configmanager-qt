QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additemdialog.cpp \
    advancedsettingsform.cpp \
    configmanager.cpp \
    connectionform.cpp \
    connectionlist.cpp \
    editmuxsettingsform.cpp \
    edittcpsettingsform.cpp \
    main.cpp \
    mainwindow.cpp \
    qconfigjsonobject.cpp \
    qtrojangoclientconfigjsonobject.cpp \
    rulelistedit.cpp

HEADERS += \
    additemdialog.h \
    advancedsettingsform.h \
    configmanager.h \
    connectionform.h \
    connectionlist.h \
    editmuxsettingsform.h \
    edittcpsettingsform.h \
    mainwindow.h \
    qconfigjsonobject.h \
    qtrojangoclientconfigjsonobject.h \
    rulelistedit.h

FORMS += \
    additemdialog.ui \
    advancedsettingsform.ui \
    connectionform.ui \
    connectionlist.ui \
    editmuxsettingsform.ui \
    edittcpsettingsform.ui \
    mainwindow.ui \
    rulelistedit.ui

TRANSLATIONS += \
    trojan-go-desktop_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
