#include <QCoreApplication>
#include "UDPrsvertest.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Udprsvertest ur;

    return a.exec();
}

