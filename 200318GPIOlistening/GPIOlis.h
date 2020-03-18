#ifndef GPIOLIS_H
#define GPIOLIS_H
#include <QThread>

class GPIOlis : public QThread {
    Q_OBJECT
    int flag=1;
public:
    GPIOlis(QObject *parent=0);
    ~GPIOlis();
    void interrupt();
    int count;
protected:
    void run();
signals:
    void ready();
};

#endif // GPIOLIS_H
