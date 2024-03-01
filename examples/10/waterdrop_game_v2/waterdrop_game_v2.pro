TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    drop.cpp \
    splash.cpp \
    gameboard.cpp

HEADERS += \
    drop.hh \
    splash.hh \
    gameboard.hh
