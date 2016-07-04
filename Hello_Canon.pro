#-------------------------------------------------
#
# Project created by QtCreator 2013-07-26T20:39:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hello_Canon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canon.cpp

HEADERS  += mainwindow.h \
    canon.h

FORMS    += mainwindow.ui

CONFIG += static
