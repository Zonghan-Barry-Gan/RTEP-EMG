#-------------------------------------------------
#
# Project created by QtCreator 2011-05-29T18:19:15
#
#-------------------------------------------------

QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


INCLUDEPATH += /home/zonghan-gan/c/lib/cppTimer-master


LIBS += /home/zonghan-gan/c/lib/cppTimer-master/libcpptimer.a

LIBS+=-lrt

TARGET = Pong
TEMPLATE = app


SOURCES += main.cpp\
        CppTimer.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    CppTimer.h

FORMS    += mainwindow.ui
