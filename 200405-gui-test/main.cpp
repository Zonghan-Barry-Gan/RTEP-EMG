/* This demo is to test the ads1115 lib self-written to sample continously
 *  no such lib for ads1115 in c++ yet.
 *  in this test demo the ads sampling is controlled by timer
 * instead of interrupt. This is not because we can't
 * This is to separate the lib and expose if any bug
 * the interrupt thread unit will soon comes out
 *  --Zonghan Gan 200318 23-39*/


#include <window.h>

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create the window
	Window window;
	window.showMaximized();

	// call the window.timerEvent function every 40 ms
    window.startTimer(1);

	// execute the application
	return app.exec();
}
