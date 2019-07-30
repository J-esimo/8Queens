TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    App.cpp
LIBS += -lsfml-system -lsfml-window -lsfml-graphics

HEADERS += \
    App.h
