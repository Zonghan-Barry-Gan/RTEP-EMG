#-------------------------------------------------
#
# Project created by QtCreator 2011-05-29T18:19:15
#
#-------------------------------------------------

QT       += core gui
QT    += widgets
greaterThan(QT_MAJOR_VERSION, X): QT += widgets

TARGET = Pong
TEMPLATE = app


SOURCES += main.cpp\
    MyEvent.cpp \
        mainwindow.cpp \
    gameplay.cpp

HEADERS  += mainwindow.h \
    MyEvent.h \
    gameplay.h

FORMS    += mainwindow.ui
