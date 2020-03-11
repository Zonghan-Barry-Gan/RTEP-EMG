#ifndef WINDOW_H
#define WINDOW_H


#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QBoxLayout>

#include "adcreader.h"

// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(); // default constructor - called when a Window is declared without arguments

	~Window();

	void timerEvent( QTimerEvent * );


// internal variables for the window class
private:
	
	QwtPlot      *plot;
	QwtPlotCurve *curve;
	double inVal;


	
	Adafruit_ADS1115 ads;
	volatile uint16_t adc0;
	//uint16_t adc1;
	//uint16_t adc2;
	//uint16_t adc3;
			
	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	//QHBoxLayout  *hLayout;  // horizontal layout

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData[plotDataSize];




	int count;

//	ADCreader *adcreader;
};

#endif // WINDOW_H
