TEMPLATE = app
CONFIG += c++11 qt
QT += core widgets
CONFIG -= app_bundle


SOURCES += main.cpp \
    drop.cpp \
    splash.cpp \
    mainwindow.cpp \
    dropitem.cpp \
    gameengine.cpp \
    splashanimation.cpp \
    splashitem.cpp \
    gameboard.cpp

HEADERS += \
    drop.hh \
    splash.hh \
    mainwindow.hh \
    dropitem.hh \
    gameengine.hh \
    splashanimation.hh \
    splashitem.hh \
    gameboard.hh
