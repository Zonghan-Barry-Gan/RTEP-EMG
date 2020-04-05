/* This demo is to test the ads1115 lib self-written to sample continously
 *  no such lib for ads1115 in c++ yet.
 *  in this test demo the ads sampling is controlled by timer
 * instead of interrupt. This is not because we can't
 * This is to separate the lib and expose if any bug
 * the interrupt thread unit will soon comes out
 *  --Zonghan Gan 200318 23-39*/

#include "window.h"
#include "ads1115.h"
#include "Iir.h"
#include <Iir.h>
#include "GPIOlis.h"

#include <cmath>  // for sine stuff
#include<stdio.h>

#include<stdlib.h>
#include <math.h>
#include <QObject>



 using namespace std;
 //set filter
 const int order = 40;

 // sampling rate here 1kHz as an example
 const float samplingrate = 860;

 const quint16 sderprt = 1117;
 const quint16 rscverprt = 1112;

 FILE *florigin = NULL;
 FILE *flhp1 = NULL;
 FILE *flpower=NULL;
 Iir::Butterworth::HighPass<order> hp1;

Window::Window(QWidget *parent): QWidget(parent)
{
        //knob = new QwtKnob;
        //gain = 2;
        count = 0;

        // set up the gain knob
        //knob->setvalue(gain);


        // // use the qt signals/slots framework to update the gain -
        // // every time the knob is moved, the setgain function will be called
        //connect( knob, signal(valuechanged(double)), slot(setgain(double)) );




        // set up the initial plot data
        for( int index=0; index<plotDataSize; ++index )
        {
            xData1[index] = index;
            yData1[index] = 0;
            xData2[index] = index;
            yData2[index] = 0;
            xData3[index] = index;
            yData3[index] = 0;


        }

        curve1 = new QwtPlotCurve;
        curve2 = new QwtPlotCurve;
        //	curve3 = new QwtPlotCurve;
        plot1 = new QwtPlot;
        plot2 = new QwtPlot;
        // make a plot curve from the data and attach it to the plot
        curve1->setSamples(xData1, yData1, plotDataSize);
        curve1->attach(plot1);
        //curve3->setSamples(xData3, yData3, plotDataSize);
        //curve3->attach(plot1);
        curve2->setSamples(xData2, yData2, plotDataSize);
        curve2->attach(plot2);

        plot1->replot();
        plot1->show();
        plot2->replot();
        plot2->show();

        // // set up the layout - knob above thermometer
        //vLayout = new QVBoxLayout;
        //vLayout->addWidget(knob);

        // plot to the left of knob and thermometer
        hLayout = new QHBoxLayout;
        //hLayout->addLayout(vLayout);
        hLayout->addWidget(plot1);
        hLayout->addWidget(plot2);
        setLayout(hLayout);




// Butterworth highpass
    const float cutoff_frequency = 50; // Hz
    const float passband_gain = 10; // db
    hp1.setup (samplingrate, cutoff_frequency);


//create file to log data
    flhp1 = fopen("flhp1ed.dat","wt");
    florigin = fopen("origin.dat","wt");
    flpower = fopen("flpowertimesmooth.dat","wt");

//initialize ads

    rftimer = new QTimer;
    //rftimer->setTimerType(Qt::PreciseTimer);
    rftimer->setInterval(20);//refresh every ~20ms
    //condition of timer start
    rftimer->start();
    connect(rftimer, &QTimer::timeout, this, &Window::plotrefresh);
//initialize UDP sender the udp has been testified and commented as not essential in this test, yet have fun if you want--Zonghan Gan
    //initialize UDP sender
    sdersc= new QUdpSocket;
    //bind local address and check
    sdersc->bind(QHostAddress("192.168.1.174"), sderprt);
    //sdersc->bind(QHostAddress::LocalHost, sderprt);
        //qDebug()<<"sender sc bind sucess";
    sumpower=0.0;
    gpiolis1=new GPIOlis();
    connect( gpiolis1, &GPIOlis::readyread, this, &Window::datapros);
    gpiolis1->start();
    //gpiolis1->wait();
}

Window::~Window() {
    delete &hp1;
//    ads1->endads();
//    delete ads1;
    gpiolis1->quit();
    delete gpiolis1;
//close the file writing
    fclose(florigin);
    fclose(flhp1);
    fclose(flpower);
}

void Window::datapros(float inval)
{
    qDebug()<<"new data feed in";
    //v=adcreader.read();
    //double inVal1 = gain * (sin(2*2.0 * M_PI  *count)+sin(10*2.0 * M_PI  *count)+sin(20*2.0 * M_PI  *count)+sin(30*2.0 * M_PI  *count)+sin(40*2.0 * M_PI  *count)+sin(50*2.0 * M_PI  *count)+sin(60*2.0 * M_PI  *count)+sin(70*2.0 * M_PI  *count)+sin(80*2.0 * M_PI  *count)+sin(90*2.0 * M_PI  *count)+sin(100*2.0 * M_PI  *count)+sin(200*2.0 * M_PI  *count));

    float inVal1= inval;
    float inVal1_2 = hp1.filter(inVal1);
    //calculate the time-smoothed power of sig before renewing the filtered data
    float inVal1_3= pow(inVal1_2,2.0);
    sumpower -=pow(yData2[0],2.0);
    sumpower += inVal1_3;
    float inVal3 = sumpower/float(plotDataSize);

    // add the new original input to the plot
    memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(float) );
    yData1[plotDataSize-1] = inVal1;


    //add the new filtered input to the plot
    memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(float) );
    yData2[plotDataSize-1] = inVal1_2;
    //add the new filtered and powered input to the plot
    memmove( yData3, yData3+1, (plotDataSize-1) * sizeof(float) );
    yData3[plotDataSize-1] = inVal3;


//save data
    fprintf(florigin,"%e\n",inVal1);
    fprintf(flhp1,"%e\n",inVal1_2);
    fprintf(flpower,"%e\n",inVal1_3);

//udp sending 1channel test to control game

    QByteArray msg;
    msg.setNum(inVal1_3);
    bool cktp;
    const float outval= msg.toFloat(&cktp);
    if (!cktp and outval != inVal1_2) qDebug() << "before sending data, data type Conversion failed";
    qDebug() << "--- Sending";
    //qDebug() << "data: " << msg;
    //send and check
    bool cksd = sdersc->writeDatagram(msg, QHostAddress("192.168.1.165"), rscverprt);
    //bool cksd = sdersc.writeDatagram(msg, QHostAddress::LocalHost, 1112);
    if(cksd>0)
      qDebug()<<"successfully send";
    else
    {
    //see the fail reason with error()
      qDebug()<<"sending is failed";
      qDebug()<<sdersc->error();

    }



    ++count;

}

//this function is used to refresh the window plot every~20ms
void Window::plotrefresh()
{

//plot
        curve1->setSamples(xData1, yData1, plotDataSize);
        plot1->replot();
        curve2->setSamples(xData3, yData3, plotDataSize);
        plot2->replot();
}
// this function can be used to change the gain of the A/D internal amplifier
//void Window::setGain(double gain)
//{
//        // for example purposes just change the amplitude of the generated input
//        this->gain = gain;
//}
