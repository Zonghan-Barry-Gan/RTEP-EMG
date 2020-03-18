#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>

class debug : public QObject
{
    Q_OBJECT
public:
//    explicit debug(QObject *parent = nullptr);
    explicit debug(QObject *parent = 0);
public slots:
    void sigin();

};

#endif // DEBUG_H
