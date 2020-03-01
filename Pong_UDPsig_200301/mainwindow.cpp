#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "gameplay.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

const quint16 PORT = 1112;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iScore ( 0 ),
    iBallDirection ( -3, -3 ),
    iP1Direction( 0 ),
    iP2Direction( 0 )
{

//    ui->setupUi(this);

//    QGraphicsScene *scene = new QGraphicsScene(this);

//    QGraphicsRectItem *iP1 = new QGraphicsRectItem(0, 0, 80, 20);
//    iP1->setBrush(QBrush(Qt::blue));
//    QGraphicsRectItem *iP2 = new QGraphicsRectItem(0, 0, 80, 20);
//    iP2->setBrush(QBrush(Qt::green));

//    QGraphicsEllipseItem *iBall = new QGraphicsEllipseItem(0, 0, 15, 15);
//    iBall->setBrush(QBrush(Qt::magenta));

//    ui->boardView->setScene(scene);
    //rsverSocket = new QUdpSocket;
    ui->setupUi(this);

    iScene = new QGraphicsScene(this);

    iP1 = new QGraphicsRectItem(0, 0, 80, 20);
    iP1->setBrush(QBrush(Qt::blue));
    iP2 = new QGraphicsRectItem(0, 0, 80, 20);
    iP2->setBrush(QBrush(Qt::green));

    iBall = new QGraphicsEllipseItem(0, 0, 15, 15);
    iBall->setBrush(QBrush(Qt::magenta));

    ui->boardView->setScene(iScene);


    iLoop = new Gameplay(*iScene, iP1, iP2, iBall, this);


    //gameplay func
    iTimer = new QTimer(this);
    iTimer->setInterval(12);
    //condition of timer start
    iTimer->start();
    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(tick()));


    iScene->setSceneRect(0, 0, 350, 320);
    iScene->addItem(iP1);
    iScene->addItem(iP2);
    iScene->addItem(iBall);

    iP1->setPos(135, 5);
    iP2->setPos(135, 300);
    iBall->setPos(150, 150);







    QSize m(iScene->sceneRect().size().width() + 10, iScene->sceneRect().size().height() + 10);
    ui->boardView->setMinimumSize(m);

    resize(minimumSize());
    //ui->boardView->installEventFilter(iLoop);

    QObject::connect(this, SIGNAL(goal(int)),this, SLOT(addScore(int)));

    QObject::connect(this, SIGNAL(P1isleft()),this, SLOT(P1Moveleft()));
    QObject::connect(this, SIGNAL(P1isright()),this, SLOT(P1Moveright()));


//receive udp sig
    rsverSocket = new QUdpSocket;
    //bind local address and port for receiving
    //local address
    //bool bdrsvsc = rsverSocket->bind(QHostAddress("172.30.141.244"), PORT);
    bool bdrsvsc = rsverSocket->bind(QHostAddress("127.0.0.1"), PORT);

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

MainWindow::~MainWindow()
{
    delete ui;
    delete rsverSocket;
}

void MainWindow::addScore(int count)
{
    iScore += count;
    ui->lcdNumber->display(iScore);
}

void MainWindow::tick()
{
    qreal newX = iBall->pos().x() + iBallDirection.x();
    qreal newY = iBall->pos().y() + iBallDirection.y();

    qreal pnewx = iP1->pos().x() + iP1Direction;
    qreal p2newx = iP2->pos().x() + iP2Direction;

    if ( ( newX < 0 ) || ( newX + iBall->boundingRect().right() > iScene->sceneRect().right() ) )
    {
        iBallDirection.rx() *= -1;
    }

    if ( ( newY < 0 ) || ( newY + iBall->boundingRect().bottom() > iScene->sceneRect().bottom() ) )
    {
        // 1 for hitting the bottom wall, -1 for hitting the top wall
        emit goal(newY / abs(newY));
        iBallDirection.ry() *= -1;
    }

    if ( ( pnewx < 0 ) || ( pnewx + iP1->boundingRect().right() > iScene->sceneRect().right() ) )
    {
        iP1Direction = 0;
    }

    if ( ( p2newx < 0 ) || ( p2newx + iP1->boundingRect().right() > iScene->sceneRect().right() ) )
    {
        iP2Direction = 0;
    }

    if ( ( iP1->collidesWithItem(iBall) ) && ( iBallDirection.y() < 0 ) )
    {
        iBallDirection.ry() *= -1;
    }

    if ( ( iP2->collidesWithItem(iBall) ) && ( iBallDirection.y() > 0 ) )
    {
        iBallDirection.ry() *= -1;
    }

    if ( qrand() % 10 == 0 )
    {
        iP2Direction = calculateP2Direction();
    }


    iBall->moveBy(iBallDirection.x(), iBallDirection.y());
    iP1->moveBy(iP1Direction, 0);
    iP2->moveBy(iP2Direction, 0);
}


qreal MainWindow::calculateP2Direction()
{
    qreal dir = 0;

    if ( iBall->pos().x() + iBallDirection.x() > iP2->sceneBoundingRect().right() )
    {
        // move right
        dir = 5;
    }
    else if ( iBall->pos().x() + iBallDirection.x() < iP2->sceneBoundingRect().left() )
    {
        // move left
        dir = -5;
    }

    return dir;

}
void MainWindow::P1Moveright()
{
    iP1Direction  = (iP1Direction == 0 ? 2 : 0);
    qDebug()<<"move right";
}
void MainWindow::P1Moveleft()
{
    iP1Direction = (iP1Direction == 0 ? -2 : 0);
    qDebug()<<"move left";
}


void MainWindow::receive()
{
    QByteArray dtstrm;
    while(rsverSocket->hasPendingDatagrams())
    {
        dtstrm.resize(rsverSocket->pendingDatagramSize());
        rsverSocket->readDatagram(dtstrm.data(), dtstrm.size());

        bool cktp2;
        const float outval= dtstrm.toFloat(&cktp2);
        if (!cktp2) qDebug() << "received but data error, data type Conversion failed";
//test outvalue
        //qDebug() << "data: " << outval;
        if (outval<0) emit P1isleft();
        else if (outval>0)
        {
            emit P1isright();
            //qDebug()<<"signal>0";
        }
    }
}
