#include "debug.h"
#include<QDebug>
debug::debug(QObject *parent) : QObject(parent)
{

}
void debug::sigin()
{
    qDebug()<<"signal in confirm";
}
