QT       += core gui widgets
TARGET = testGridLayout
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../fixedaspectratioitem.cpp \
    customtoolbutton.cpp \
    main_testGridLayout.cpp \
    mainwindow_grid_layout_test.cpp \
    ../cellbutton.cpp \
    ../iconcellbutton.cpp \
    ../animatediconbutton.cpp \
    ../basic_defs.cpp \
    testwidgetitem.cpp

HEADERS += \
    ../fixedaspectratioitem.h \
    customtoolbutton.h \
    mainwindow_grid_layout_test.h \
    ../iconcellbutton.h \
    ../cellbutton.h \
    ../animatediconbutton.h \
    ../basic_defs.hpp \
    testwidgetitem.h

RESOURCES += \
    ../images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
