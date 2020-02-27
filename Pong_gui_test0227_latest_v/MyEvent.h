#ifndef MYEVENT_H
#define MYEVENT_H

#include <QCoreApplication>
#include <QEvent>
#include <QObject>
#include <QDebug>
#include <iostream>


static const QEvent::Type MyEventType = (QEvent::Type)QEvent::registerEventType(QEvent::User+100);

//长官
class MyEvent: public QEvent
{
//    Q_OBJECT //必须包含的宏
public:
    MyEvent(Type MyEventType):QEvent(MyEventType){}
    int ch;
    float sg;
    void set_ch(int channel);
//public slots :
    void load_sg(float value);
};

////信使
//class MySender: public QCoreApplication
//{
//public:
//    MySender(int argc,char *argv[]):QCoreApplication(argc,argv){}

//public:
//    bool notify(QObject *receiver, QEvent *event);

//};


#endif // MYEVENT_H
