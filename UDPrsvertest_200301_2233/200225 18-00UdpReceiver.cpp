#include <QByteArray>
#include <iostream>
#include "UDPrsvertest.h"
#include <QUdpSocket>

const quint16 PORT = 1112;

Udprsvertest::Udprsvertest(QObject *p) :
    QObject(p)
{
    rsverSocket = new QUdpSocket;
    rsverSocket->bind(QHostAddress("127.0.0.1"), PORT);
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
