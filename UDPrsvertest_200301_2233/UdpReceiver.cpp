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
    bool bdrsvsc = rsverSocket->bind(QHostAddress("172.30.156.14"), PORT);

    //bool bdrsvsc = rsverSocket->bind(QHostAddress::LocalHost, PORT);
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
    QByteArray dtstrm;
    while(rsverSocket->hasPendingDatagrams())
    {
        dtstrm.resize(rsverSocket->pendingDatagramSize());
        rsverSocket->readDatagram(dtstrm.data(), dtstrm.size());

        bool cktp2;
        const float outval= dtstrm.toFloat(&cktp2);
        if (!cktp2) qDebug() << "received but data error, data type Conversion failed";

        qDebug() << "data: " << outval;
    }
}
//inspired by https://blog.csdn.net/weixin_42216430/article/details/80780297

