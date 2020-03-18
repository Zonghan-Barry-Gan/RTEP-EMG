#include "GPIOlis.h"
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
//listen to GPIO 23
#define int BUTTON_PIN 4
GPIOlis::GPIOlis(QObject *parent): QThread(parent)
{
count=0;
}
void GPIOlis::interrupt()
{
    emit ready();
    count ++;
    qDebug()<<"conversion ready";

}
GPIOlis::~GPIOlis() {
}

void GPIOlis::run() {
    if (wiringPiSetup () < 0) {
          qDebug()<< "Unable to setup wiringPi";
          flag=0;
      }

    if ( wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &GPIOlis::interrupt) < 0 )
    {
        qDebug()<<"unable to set up listensing";
        flag=0;
    }
    while(flag)
    {
    this->usleep(1000);
    }
    return;
}
