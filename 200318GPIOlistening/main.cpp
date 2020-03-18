#include <QCoreApplication>
#include "GPIOlis.h"
#include "debug.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GPIOlis GPIO23;
    debug debug;
    QObject::connect(&GPIO23,SIGNAL(ready()),&debug,SIGNAL(signin()));
    GPIO23.start();
    GPIO23.wait();
    return a.exec();
}
