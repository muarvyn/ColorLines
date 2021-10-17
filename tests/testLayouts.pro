QT       += core gui widgets
TARGET = testLayouts
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../aspectratioitem.cpp \
    ../swapboxlayout.cpp \
    ../tradeforsizeitem.cpp \
    customtoolbutton.cpp \
    mainwindow_layout_test.cpp

HEADERS += \
    ../aspectratioitem.h \
    ../intermediateitemlayout.h \
    ../swapboxlayout.h \
    ../swappablelayout.h \
    ../tradeforsizeitem.h \
    customtoolbutton.h \
    mainwindow_layout_test.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../testlayouts.qmodel

