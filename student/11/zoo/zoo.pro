TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    animal.cpp \
    bird.cpp \
    cockatoo.cpp \
    giraffe.cpp \
    mammal.cpp \
    owl.cpp 

HEADERS += \
    animal.hh \
    bird.hh \
    cockatoo.h \
    giraffe.h \
    mammal.h \
    owl.hh 
