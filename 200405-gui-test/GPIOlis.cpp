#include "GPIOlis.h"
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <functional>
#include <QFile>

int gpipinterrupt=0;
std::mutex cmdmtx;
using namespace std;

void interrupt2(void)
{
    
    //qDebug()<<"interrupt";
    cmdmtx.lock();
    gpipinterrupt =1;
    cmdmtx.unlock();
    }
int ReadLine(float data1[30000],float data2[30000])
{

    QFile file1("/home/zonghan-gan/qt/txtrd/Alternating_4Channel_Part1.dat");
    QFile file2("/home/zonghan-gan/qt/txtrd/Alternating_4Channel_Part2.dat");
    if (file1.open(QIODevice::ReadOnly | QIODevice::Text)&file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //float data[30000];
        int i=0;
        bool cktp2;
        while (!file1.atEnd()&!file2.atEnd()&(i<30000))
        {

            QByteArray line1 = file1.readLine();
            QByteArray line2 = file2.readLine();
//            QString str(line);
            data1[i]= line1.toFloat(&cktp2);
            data2[i]= line2.toFloat(&cktp2);
//            qDebug() << "reading";
//            qDebug() << data[i];
//            displayStporing << str;
            i++;
        }
        file1.close();
        file2.close();
        qDebug()<<"end reading";
        return 1;
        //return data[29999];
    }
}


GPIOlis::GPIOlis(QObject *parent): QThread(parent)
{
count=0;
//ads1=new ads1115(0x48);
//connect(this, &GPIOlis::ready, ads1, &ads1115::readsig);
//qDebug()<<"thread set up";
ReadLine(this->data1,this->data2);
}
void GPIOlis::interrupt(void)
{
    //emit ready();
    count ++;
    qDebug()<<"gpio awake, conversion ready";
    gpipinterrupt=0;
    float voltage=ads1->readsig();
    emit readyread(voltage);
    //qDebug()<<"data read";
    return;
}
GPIOlis::~GPIOlis() {
}

void GPIOlis::run() {
    if (wiringPiSetup () < 0) {
          qDebug()<< "Unable to setup wiringPi";
          flag=0;
      }


    if ( wiringPiISR (1, INT_EDGE_RISING, &interrupt2) < 0 )
    {
        qDebug()<<"unable to set up listensing";
        flag=0;
    }
    while(flag)
    {   
        
        cmdmtx.lock();
        //qDebug()<<"test"<<gpipinterrupt;
        if(gpipinterrupt)
        {
            
            this->interrupt();
        }
        cmdmtx.unlock();    
        this->usleep(1000);
    }
    return;
}
void GPIOlis::quit()
{
    ads1->endads();
    delete ads1;
    QThread::quit();
}
