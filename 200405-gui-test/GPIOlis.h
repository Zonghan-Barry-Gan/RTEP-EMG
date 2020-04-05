#ifndef GPIOLIS_H
#define GPIOLIS_H
#include <QThread>
//#include "ads1115.h"
#include <QTimer>
extern int gpipinterrupt;
class GPIOlis : public QThread {
    Q_OBJECT
    int flag=1;
public:
    GPIOlis(QObject *parent=0);
    ~GPIOlis();
    void interrupt(void);
    int count;
    void quit();
    float data1[30000];
    float data2[30000];
    QTimer sdtmr;
    rdtimer = new QTimer;
    rdtimer->setTimerType(Qt::PreciseTimer);
    rdtimer->setInterval(5);//read signal every 2 ms
//private:
//    ads1115* ads1;
protected:
    void run();
signals:
    void ready();
    void readyread(float voltage);
};

#endif // GPIOLIS_H
