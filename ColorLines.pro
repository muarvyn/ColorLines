#-------------------------------------------------
#
# Project created by QtCreator 2018-08-16T20:57:31
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ColorLines
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -Wno-sign-compare
CONFIG += c++11
INCLUDEPATH += ../include

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    board.cpp \
    cellbutton.cpp \
    dijkstra_search.cpp \
    cellgridcontrol.cpp \
    iconcellbutton.cpp \
    animatediconbutton.cpp \
    gameboard.cpp \
    gamecontrol.cpp \
    fixedaspectratioitem.cpp \
    boardinfo.cpp

HEADERS += \
        mainwindow.h \
    board.h \
    cellbutton.h \
    basic_defs.hpp \
    dijkstra_search.hpp \
    cellgridcontrol.h \
    iconcellbutton.h \
    animatediconbutton.h \
    gameboard.h \
    gamecontrol.h \
    fixedaspectratioitem.h \
    boardinfo.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

FORMS += \
    mainwindow.ui
