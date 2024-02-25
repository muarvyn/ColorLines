QT       += core gui widgets
TARGET = testColorLines
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../layout/transposableboxlayout.cpp \
    ../layout/util.cpp \
    mainwindow_test.cpp \
    ../cellbutton.cpp \
    ../iconcellbutton.cpp \
    ../animatediconbutton.cpp \
    ../basic_defs.cpp

HEADERS += \
    ../layout/transposable.h \
    ../layout/transposableboxlayout.h \
    mainwindow_test.h \
    ../iconcellbutton.h \
    ../cellbutton.h \
    ../animatediconbutton.h \
    ../basic_defs.hpp

RESOURCES += \
    ../images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
