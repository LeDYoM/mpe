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
    renderbuffer.cpp \
    opengluser.cpp \
    shadermanager.cpp \
    renderobject.cpp \
    texturemanager.cpp

HEADERS  += mainwindow.h \
    mpeapplication.h \
    mpeglwidget.h \
    log.h \
    materialmanager.h \
    renderbuffer.h \
    singleton.h \
    memm.h \
    buffertype.h \
    opengluser.h \
    shadermanager.h \
    globalwrapperh.h \
    renderobject.h \
    texturemanager.h

RESOURCES += \
    resources.qrc
