QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mpe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mpeapplication.cpp \
    mpeglwidget.cpp \
    materialmanager.cpp \
    openglmanager.cpp \
    renderbuffer.cpp

HEADERS  += mainwindow.h \
    mpeapplication.h \
    mpeglwidget.h \
    log.h \
    materialmanager.h \
    openglmanager.h \
    renderbuffer.h
