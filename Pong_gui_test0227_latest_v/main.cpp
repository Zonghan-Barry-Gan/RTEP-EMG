#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include "MyEvent.h"
#include <iostream>
#include <cmath>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    for (int i = 0; i < 1000; i++) {
        auto *myEvent1 = new MyEvent(MyEventType);
        myEvent1->set_ch(1);
        myEvent1->load_sg(sin(0.005*i*3.1415926/2));
        QCoreApplication::postEvent(&w, myEvent1);
        //QCoreApplication::postEvent(ui->boardView, myEvent1);
    }



    return a.exec();
}


//    for(int i=0;i<1000;i++){
//    MyEvent myEvent1(MyEventType);
//    myEvent1.set_ch(1);
//    myEvent1.load_sg(sin(0.005*i*3.1415926/2));
//    QCoreApplication::postEvent(&w, &myEvent1);
//    }


//原项目main.cpp

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    MainWindow w;
//    w.show();

//    return a.exec();
//}
