#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T16:32:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configreader.cpp \
    servermonitor.cpp \
    notification.cpp \
    threadping.cpp

HEADERS  += mainwindow.h \
    configreader.h \
    servermonitor.h \
    notification.h \
    threadping.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

