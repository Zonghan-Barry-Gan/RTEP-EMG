#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void addScore(int count);

//private:

};

#endif // MAINWINDOW_H
