#include "statespace.h"

StateSpace::StateSpace(double x1,double x2,double x3,double a11,double a12,double a13,double a21,double a22,double a23,double a31,double a32,double a33,double b1,double b2,double b3,double c1,double c2,double c3,double d)
{
    m_integrator_x1=new Integrator(x1);
    m_integrator_x2=new Integrator(x2);
    m_integrator_x3=new Integrator(x3);

    m_a11=a11;
    m_a12=a12;
    m_a13=a13;
    m_a21=a21;
    m_a22=a22;
    m_a23=a23;
    m_a31=a31;
    m_a32=a32;
    m_a33=a33;

    m_b1=b1;
    m_b2=b2;
    m_b3=b3;

    m_c1=c1;
    m_c2=c2;
    m_c3=c3;

    m_d=d;
}

StateSpace::~StateSpace()
{
    delete m_integrator_x1;
    delete m_integrator_x2;
    delete m_integrator_x3;
}

double StateSpace::getoutput()
{
    return m_c1*m_integrator_x1->state()+
           m_c2*m_integrator_x2->state()+
           m_c3*m_integrator_x3->state()+ m_d*m_previous_input;
}

double StateSpace::update(double input, double dt)
{
    double tmp_x1=m_integrator_x1->state();
    double tmp_x2=m_integrator_x2->state();
    double tmp_x3=m_integrator_x3->state();
    double output=getoutput();
    m_integrator_x1->update(m_a11*tmp_x1+m_a12*tmp_x2+m_a13*tmp_x3+m_b1*input,dt);
    m_integrator_x2->update(m_a21*tmp_x1+m_a22*tmp_x2+m_a23*tmp_x3+m_b2*input,dt);
    m_integrator_x3->update(m_a31*tmp_x1+m_a32*tmp_x2+m_a33*tmp_x3+m_b3*input,dt);
    m_previous_input=input;
    return output;
}
