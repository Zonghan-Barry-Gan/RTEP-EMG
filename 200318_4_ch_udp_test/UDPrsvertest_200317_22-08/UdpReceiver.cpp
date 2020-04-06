#include <QByteArray>
#include <iostream>
#include "UDPrsvertest.h"
#include <QUdpSocket>

const quint16 PORT = 1112;

Udprsvertest::Udprsvertest(QObject *p) :
    QObject(p)
{
    rsverSocket = new QUdpSocket;
    //bind local address and port for receiving
    //bool bdrsvsc = rsverSocket->bind(QHostAddress("172.30.141.244"), PORT);
    //bool bdrsvsc = rsverSocket->bind(QHostAddress("172.30.156.14"), PORT);

    bool bdrsvsc = rsverSocket->bind(QHostAddress::LocalHost, PORT);
    if(bdrsvsc>0)
      { qDebug()<<"bind success";
        qDebug() << "--- receiving--";
    }
    else
    {
        qDebug()<<"bind failed";
        qDebug()<<rsverSocket->error();
    }
    connect(rsverSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

Udprsvertest::~Udprsvertest()
{
    delete rsverSocket;
}

void Udprsvertest::receive()
{
//    QByteArray dtstrm;
    while(rsverSocket->hasPendingDatagrams())
    {
//        dtstrm.resize(rsverSocket->pendingDatagramSize());




        //  QByteArray transform back into float[]
        float  outFval[4];

        //float  fVar[4] = { 1.0, 1.0, 1.0, 1.0 };//set size of any array with 4 float

        //int len_fVar = sizeof(fVar); // 4*4 = 16 calculate the size
        rsverSocket->readDatagram((char*)outFval, sizeof(outFval));

//        memcpy(&outFval, dtstrm.data(), len_fVar);


        qDebug() << "data: " << outFval[0]<<outFval[1]<<outFval[2]<<outFval[3];
    }
}

//inspired by https://blog.csdn.net/weixin_42216430/article/details/80780297

