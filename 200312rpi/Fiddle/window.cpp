#include "window.h"
//#include "adcreader.h"

#include <cmath>  // for sine stuff


Window::Window() : count(0)
{
    // set up the initial plot data
    for( int index=0; index<plotDataSize; ++index )
    {
	xData[index] = index;
	yData[index] =  sin( M_PI * index/50.0 );

    }

    curve = new QwtPlotCurve;
    plot = new QwtPlot;

    // make a plot curve from the data and attach it to the plot
    curve->setSamples(xData, yData, plotDataSize);
    curve->attach(plot);

    plot->replot();
    plot->show();

    vLayout = new QVBoxLayout;
    vLayout->addWidget(plot);

    setLayout(vLayout);

    ads.setGain(adsGain_t::GAIN_ONE);
    ads.begin();
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
//	adcreader->quit();
	// wait until the run method has terminated
//	adcreader->wait();
//	delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
     adc0 = ads.readADC_SingleEnded(0);
    

     
    //printBits(sizeof(adc0), &adc0);

    //double inVal = sin(M_PI*count/50.0);
    uint16_t inVal = adc0;

	printf("adc = %d\n",inVal);
    //printf("adc = %f\n",inVal);
    ++count;
    
    // add the new input to the plot
    memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
    yData[plotDataSize-1] = inVal;
    curve->setSamples(xData, yData, plotDataSize);
    plot->replot();
}
