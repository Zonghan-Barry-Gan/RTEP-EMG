#include <QByteArray>
#include <QCoreApplication>
#include <QHostAddress>
#include <QUdpSocket>


using namespace std;
const quint16 sderprt = 1111;

const quint16 rscverprt = 1112;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//define the port of the socket
    QUdpSocket sdersc;
    sdersc.bind(QHostAddress("127.0.0.1"), sderprt);
//    QByteArray msg = "Hello world!";

//    int  dt[4] = {0x3,0x3,0x3,0x3};//初始化变量赋值

//    QByteArray msg;
//    int len_dt = sizeof(dt); // 4*4 = 16 (float占4个字节)
//    msg.resize(len_dt);
//    memcpy(msg.data(), &dt, len_dt);
//    int  outIntVar[4];
//    memcpy(&outIntVar, msg.data(), len_dt);

    float dt = 20.0;
    QByteArray msg;
    for(int i=0; i<100; i++){

        dt=dt+1.0;
        msg.setNum(dt);
        bool cktp;
        const float outval= msg.toFloat(&cktp);
        if (!cktp and outval != dt) qDebug() << "before sending data, data type Conversion failed";
        qDebug() << "--- Sending";
        qDebug() << "data: " << msg;
 //       qDebug() << "sendingtest " << msg;
        qDebug() << "sendingtest " << outval;
        sdersc.writeDatagram(msg, QHostAddress("127.0.0.1"), rscverprt);
        }
    return a.exec();
}

// inspired by https://blog.csdn.net/weixin_42216430/article/details/80780297
