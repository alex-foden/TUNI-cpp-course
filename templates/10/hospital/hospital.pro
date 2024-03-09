TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    person.cpp \
    date.cpp \
    careperiod.cpp \
    hospital.cpp \
    cli.cpp \
    utils.cpp

HEADERS += \
    person.hh \
    date.hh \
    careperiod.hh \
    hospital.hh \
    cli.hh \
    utils.hh
