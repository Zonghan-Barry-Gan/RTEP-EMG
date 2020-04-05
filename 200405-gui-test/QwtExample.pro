# Qt project file - qmake uses his to generate a Makefile

QT       += core gui network

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /home/pi/c/iir1/

LIBS += /home/pi/c/iir1/libiir_static.a

NCLUDEPATH    += /home/ember/opt/rasp-pi-rootfs/usr/local/include
LIBS += -L/home/ember/opt/rasp-pi-rootfs/usr/local/lib -lwiringPi

TARGET = QwtExample

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm

HEADERS += window.h \
    GPIOlis.h

SOURCES += main.cpp window.cpp \
    GPIOlis.cpp
