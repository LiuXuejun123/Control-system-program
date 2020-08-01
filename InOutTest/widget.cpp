#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <math.h>

// --------------------------
// Set stop time here
// --------------------------
#define ENDOFTIME 3
#define SAMPLINGTIMEMSEC 10
// --------------------------
// Set stop time here
// --------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	// Create dir for logs
	if (!QDir("logs").exists()) {
		QDir().mkdir("logs");
	}

    // Set window size
	this->setMinimumSize(640, 480);

    // Add main layout with two plots
    mainlayout = new QGridLayout(this);
    inputPlot = new QCustomPlot(this);
    outputPlot = new QCustomPlot(this);
	mainlayout->addWidget(inputPlot, 0, 0);
	mainlayout->addWidget(outputPlot, 0, 1);



	startButton = new QPushButton("Start");
	connect(startButton, &QPushButton::clicked, this, [=](){
		startTime = 0;
		relativeTime = 0;
        inputPlot->addGraph();
		inputPlot->graph(0)->data()->clear();
        inputPlot->graph(0)->setPen(QPen(Qt::blue));
        inputPlot->graph(0)->setName("Continuous");
        inputPlot->addGraph();
        inputPlot->graph(1)->data()->clear();
        inputPlot->graph(1)->setPen(QPen(Qt::red));
        inputPlot->graph(1)->setName("Discrete");
        outputPlot->addGraph();
		outputPlot->graph(0)->data()->clear();
        outputPlot->graph(0)->setPen(QPen(Qt::blue));
        outputPlot->addGraph();
        outputPlot->graph(1)->data()->clear();
        outputPlot->graph(1)->setPen(QPen(Qt::red));
		timer->start();
	});
	mainlayout->addWidget(startButton, 1, 0);

	saveButton = new QPushButton("Save");
	connect(saveButton, &QPushButton::clicked, this, [=](){
		QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
		inputPlot->savePng(QString("./logs/%1_input.png").arg(timestamp));
		outputPlot->savePng(QString("./logs/%1_output.png").arg(timestamp));
	});
	mainlayout->addWidget(saveButton, 1, 1);

    // Give the axes some labels:
    inputPlot->xAxis->setLabel("t");
    inputPlot->yAxis->setLabel("input");
    outputPlot->xAxis->setLabel("t");
    outputPlot->yAxis->setLabel("output");

    // --------------------------
    // Change ranges if you need！！！！！
    // --------------------------
    // Set axes ranges so see all data:
    inputPlot->xAxis->setRange(0, ENDOFTIME);
    inputPlot->yAxis->setRange(-0.5, 2);
    outputPlot->xAxis->setRange(0, ENDOFTIME);
    outputPlot->yAxis->setRange(-0.5, 3);

    // --------------------------
    // Create the object here
    // --------------------------
   // object = new gain(2.0);
   // m_integrator=new Integrator(0.0);
    //m_simplesystem = new simplesystem(0.0);
    m_StateSpace = new StateSpace(0.0,0.0,0.0,-10,0,0,0,-5,0,0,0,-2.5,2,3,1,10,0,0.7,0);
    m_StateSpace_input = new StateSpace(1.0,0,0,
                                        -3,0,0,
                                        0,0,0,
                                        0,0,0,
                                        0,0,0,
                                        1,0,0,
                                        0);
    m_Discrete1=new Discrete(0.0,0.0,0.0,
                             0.135335283236613,	0,	0,
                             0,	0.367879441171442,	0,
                             0,	0,	0.606530659712633,
                             0.172932943352677,
                             0.379272335297135,
                             0.157387736114947,
                             10,	0,	0.700000000000000,0);

    m_Discrete2=new Discrete(0.0,0.0,0.0,
                             0.716531310573789,0,0,
                             0,0.846481724890614,0,
                             0,0,0.920044414629323,
                             0.0566937378852422,
                             0.0921109650656316,
                             0.0319822341482707,
                             10,0,0.7,0);

    m_Discrete3=new Discrete(0.0,0.0,0.0,
                             0.904837418035960,0,0,
                             0,0.951229424500714,0,
                             0,0,0.975309912028333,
                             0.0190325163928081,
                             0.0292623452995716,
                             0.00987603518866693,
                             10,0,0.7,0);
                        /*
                        * Discrete(x1,x2,x3,
                        *          a11,a12,a13,
                        *          a21,a22,a23,
                        *          a31,a32,a33,
                        *           b1,b2,b3,
                        *          c1,c2,c3,d)
                        *
                        */
    m_Discrete_input1=new Discrete(1.0,0.0,0.0,
                                   0.548811636094026,0, 0,
                                   0,0,0,
                                   0,0,0,
                                   0,0,0,
                                   1,0,0,0);//0.2s u
    m_Discrete_input2=new Discrete(1.0,0.0,0.0,
                                   0.904837418035960,0, 0,
                                   0,0,0,
                                   0,0,0,
                                   0,0,0,
                                   1,0,0,0);//0.033s u
    m_Discrete_input3=new Discrete(1.0,0.0,0.0,
                                   0.970445533548508,0, 0,
                                   0,0,0,
                                   0,0,0,
                                   0,0,0,
                                   1,0,0,0);//0.01s u


    // --------------------------
    // Create the object here
    // --------------------------

    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // --------------------------
    // Set sampling time here
    // --------------------------
	timer->setInterval(SAMPLINGTIMEMSEC);
    // --------------------------
    // Set sampling time here
    // --------------------------
}

Widget::~Widget()
{
    delete ui;
    delete inputPlot;
    delete outputPlot;
    delete timer;
    delete mainlayout;

    // --------------------------
    // Delete the object here
    // --------------------------
    delete m_StateSpace;
    delete m_StateSpace_input;
    delete m_Discrete1;
    delete m_Discrete2;
    delete m_Discrete3;
    delete m_Discrete_input1;
    delete m_Discrete_input2;
    delete m_Discrete_input3;
    // --------------------------
    // Delete the object here
    // --------------------------
}

void Widget::update() {

	// --------------------------
	// Replace input signal with ours
	// --------------------------
    double signal = std::exp(-1*relativeTime / 1000.0)* std::exp(-2*relativeTime / 1000.0);
    double sig =0.0;
	// --------------------------
	// Replace input signal with ours
	// --------------------------

	// --------------------------
	// Plot initial values here
	// --------------------------
	if (startTime == 0) {
		// First step only plot initial values
		startTime = QDateTime::currentMSecsSinceEpoch();

		inputPlot->graph(0)->addData(0.0, 0);
		outputPlot->graph(0)->addData(0.0, 0);
        outputPlot->graph(1)->addData(0.0, 0);
		return;
	} else {
		dt = relativeTime;
		relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
        dt = relativeTime - dt;
    }

    inputPlot->graph(0)->addData(relativeTime / 1000.0, m_StateSpace_input->getoutput());
    inputPlot->graph(1)->addData(relativeTime / 1000.0,m_Discrete_input3->getoutput());
    outputPlot->graph(0)->addData(relativeTime / 1000.0, m_StateSpace->getoutput());
    outputPlot->graph(1)->addData(relativeTime / 1000.0, m_Discrete3->getoutput());


    inputPlot->replot();
    outputPlot->replot();

    // --------------------------
    // Update the object here
    // --------------------------
    //object->update(signal);
    m_StateSpace_input->update(sig,dt/1000.0);
    m_StateSpace->update(m_StateSpace_input->getoutput(),dt/1000.0);
                             //sig=0
    m_Discrete_input1->update(sig);
    m_Discrete1->update(m_Discrete_input1->getoutput());
    m_Discrete_input2->update(sig);
    m_Discrete2->update(m_Discrete_input2->getoutput());
    m_Discrete_input3->update(sig);
    m_Discrete3->update(m_Discrete_input3->getoutput());
    //m_integrator->update(signal,double(dt)/1000.0);
    // --------------------------
    // Update the object here
    // --------------------------

	if (relativeTime / 1000.0 > ENDOFTIME) {
		timer->blockSignals(true);
		timer->stop();
		timer->blockSignals(false);
	}
}
