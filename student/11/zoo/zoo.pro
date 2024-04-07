TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    animal.cpp \
    bird.cpp \
    owl.cpp 

HEADERS += \
    animal.hh \
    bird.hh \
    owl.hh 
