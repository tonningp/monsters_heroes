#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T14:48:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tutorial02
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sprite.cpp \
    ctilescene.cpp

HEADERS  += mainwindow.h \
    sprite.h \
    ctilescene.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
