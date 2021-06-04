QT       += core gui widgets
TARGET = testLayouts
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../centralitemlayout.cpp \
    customtoolbutton.cpp \
    ../fixedaspectratioitem.cpp \
    main_layout_test.cpp \
    mainwindow_layout_test.cpp

HEADERS += \
    ../centralitemlayout.h \
    customtoolbutton.h \
    ../fixedaspectratioitem.h \
    mainwindow_layout_test.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../centralitemlayout.qmodel \
    ../testlayouts.qmodel

