#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T19:29:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dsmTT
TEMPLATE = app


SOURCES += main.cpp \
    mainWindow.cpp \
    dsmModel.cpp \
    clusterModel.cpp \
    globalInst.cpp

HEADERS  += \
    mainWindow.h \
    dsmModel.h \
    clusterModel.h \
    globalInst.h

FORMS    += \
    mainWindow.ui
