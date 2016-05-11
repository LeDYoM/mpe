QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mpe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mpeapplication.cpp \
    mpeglwidget.cpp \
    mpeopenglcontext.cpp \
    camera.cpp

HEADERS  += \
    mpeopenglcontext.hpp \
    log.hpp \
    mainwindow.hpp \
    memm.hpp \
    mpeapplication.hpp \
    mpeglwidget.hpp \
    camera.hpp
