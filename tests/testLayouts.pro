QT       += core gui widgets
TARGET = testLayouts
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../layout/sizehintitem.cpp \
    ../layout/transposableboxlayout.cpp \
    ../layout/util.cpp \
    customtoolbutton.cpp \
    mainwindow_layout_test.cpp

HEADERS += \
    ../layout/sizehintitem.h \
    ../layout/transposable.h \
    ../layout/transposableboxlayout.h \
    customtoolbutton.h \
    mainwindow_layout_test.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../testlayouts.qmodel

