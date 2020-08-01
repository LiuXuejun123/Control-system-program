#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include "qcustomplot.h"
#include "blocks/gain/gain.h"
#include"blocks/integrator/integrator.h"
#include"blocks/simplesystem.h/simplesystem.h"
#include"blocks/StateSpace/statespace.h"
#include"blocks/Discrete/discrete.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update();

private:
    Ui::Widget *ui;
    QGridLayout *mainlayout;
    QCustomPlot *inputPlot;
    QCustomPlot *outputPlot;
	QPushButton* startButton;
	QPushButton* saveButton;

	qint64 startTime = 0;
	qint64 relativeTime = 0;
	qint64 dt;

    QTimer * timer;

    // --------------------------
    // Add pointer to the object here
    // --------------------------
    //gain *object;   // <=
    //Integrator *m_integrator;
    //simplesystem *m_simplesystem;
    StateSpace *m_StateSpace;
    StateSpace *m_StateSpace_input;
    Discrete *m_Discrete1;
    Discrete *m_Discrete2;
    Discrete *m_Discrete3;
    Discrete *m_Discrete_input1;
    Discrete *m_Discrete_input2;
    Discrete *m_Discrete_input3;
    // --------------------------
    // Add pointer to the object here
    // --------------------------
};

#endif // WIDGET_H
