#include <QByteArray>
#include <QCoreApplication>
#include <QHostAddress>
#include <QUdpSocket>


using namespace std;
const quint16 sderprt = 1117;

const quint16 rscverprt = 1112;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//define the port of the socket
    QUdpSocket sdersc;
    //bind local address and check
    //if(sdersc.bind(QHostAddress("192.168.43.231"), sderprt)>0);
    if(sdersc.bind(QHostAddress::LocalHost, sderprt)>0);
        qDebug()<<"sender sc bind sucess";
//    sdersc.bind(QHostAddress("172.30.156.14"), sderprt);
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
    for(int i=0; i<10000000; i++){

        dt=dt*-1.0;
        msg.setNum(dt);
        bool cktp;
        const float outval= msg.toFloat(&cktp);
        if (!cktp and outval != dt) qDebug() << "before sending data, data type Conversion failed";
        qDebug() << "--- Sending";
        qDebug() << "data: " << msg;
 //       qDebug() << "sendingtest " << msg;
        qDebug() << "sendingtest " << outval;
        //send and check
//        bool cksd = sdersc.writeDatagram(msg, QHostAddress("192.168.43.30"), rscverprt);
        bool cksd = sdersc.writeDatagram(msg, QHostAddress("127.0.0.1"), rscverprt);
        //bool cksd = sdersc.writeDatagram(msg, QHostAddress::AnyIPv4, 1112);
        //bool cksd = sdersc.writeDatagram(msg, QHostAddress::LocalHost, 1112);
        if(cksd>0)
            qDebug()<<"successfully send";
        else
        {
        //可调用error()函数，查看bind不成功的原因
            qDebug()<<"sending is failed";
            qDebug()<<sdersc.error();

        }

        //sdersc.writeDatagram(msg, QHostAddress("172.30.141.244"), rscverprt);
        }
    return a.exec();
}

// inspired by https://blog.csdn.net/weixin_42216430/article/details/80780297
