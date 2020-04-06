#include <QApplication>
#include "mainwindow.h"
#include <QScreen>

int main(int argc, char *argv[])
{
    //resize
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QScreen *iScreen = a.primaryScreen();
    QSize rScreenSize = iScreen->size();
    MainWindow w(rScreenSize.rwidth(),rScreenSize.rheight());
    w.show();

    return a.exec();
}
