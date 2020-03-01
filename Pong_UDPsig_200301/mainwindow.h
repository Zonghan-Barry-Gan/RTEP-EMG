#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QObject>
#include <QUdpSocket>

class QGraphicsItem;
class QTimer;

class Gameplay;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    Gameplay *iLoop;
    int iScore;
//graphic item in gameplay
    QGraphicsScene * iScene;
    QGraphicsRectItem *iP1, *iP2;
    QGraphicsEllipseItem *iBall;
    QTimer *iTimer;

    QPointF iBallDirection;
    qreal iP1Direction;
    qreal iP2Direction;
    qreal calculateP2Direction();
    //QUdpSocket *rsverSocket;
public slots:
    void addScore(int count);
    void tick();
    void P1Moveleft();
    void P1Moveright();



signals:
    void goal(int player);
    void P1isleft();
    void P1isright();


//for udp receive
public slots:
    void receive();

private:
    QUdpSocket *rsverSocket;
};

#endif // MAINWINDOW_H
