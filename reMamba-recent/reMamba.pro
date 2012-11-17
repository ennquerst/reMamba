#-------------------------------------------------
#
# Project created by QtCreator 2012-10-11T11:08:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reMamba
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fate.cpp \
    spider.cpp \
    webpath.cpp

HEADERS  += mainwindow.h \
    constants.h \
    fate.h \
    spider.h \
    webpath.h

FORMS    += mainwindow.ui

RESOURCES += \
    pics.qrc
