QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/theme/qthemeconfig.cpp \
    src/ui/additemdialog.cpp \
    src/ui/advancedsettingsform.cpp \
    src/config/configmanager.cpp \
    src/ui/connectionform.cpp \
    src/ui/connectionlist.cpp \
    src/ui/editmuxsettingsform.cpp \
    src/ui/edittcpsettingsform.cpp \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/config/qconfigjsonobject.cpp \
    src/config/qtrojangoclientconfigjsonobject.cpp \
    src/ui/rulelistedit.cpp \
    src/proxy/systemproxymanager.cpp \
    src/traymenu/traymenu.cpp \
    src/trojan/trojangomanger.cpp

HEADERS += \
    src/theme/qthemeconfig.h \
    src/ui/additemdialog.h \
    src/ui/advancedsettingsform.h \
    src/config/configmanager.h \
    src/ui/connectionform.h \
    src/ui/connectionlist.h \
    src/ui/editmuxsettingsform.h \
    src/ui/edittcpsettingsform.h \
    src/ui/mainwindow.h \
    src/config/qconfigjsonobject.h \
    src/config/qtrojangoclientconfigjsonobject.h \
    src/ui/rulelistedit.h \
    src/proxy/systemproxymanager.h \
    src/traymenu/traymenu.h \
    src/trojan/trojan-go-start.h \
    src/trojan/trojangomanger.h

FORMS += \
    ui/additemdialog.ui \
    ui/advancedsettingsform.ui \
    ui/connectionform.ui \
    ui/connectionlist.ui \
    ui/editmuxsettingsform.ui \
    ui/edittcpsettingsform.ui \
    ui/mainwindow.ui \
    ui/rulelistedit.ui

TRANSLATIONS += \
    trojan-go-desktop_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    res/qss.qrc \
    res/res.qrc

win32: LIBS += -lwininet

win32: LIBS += -lrasapi32

win32: LIBS += -L$$PWD/lib/windows/ -ltrojan-go-start

INCLUDEPATH += $$PWD/lib/windows
DEPENDPATH += $$PWD/lib/windows
