#include "discrete.h"

Discrete::Discrete(double x1,double x2,double x3,
                   double a11,double a12,double a13,
                   double a21,double a22,double a23,
                   double a31,double a32,double a33,
                   double b1,double b2,double b3,
                   double c1,double c2,double c3,double d):
 m_x1(x1),m_x2(x2),m_x3(x3),m_a11(a11),m_a12(a12),m_a13(a13),m_a21(a21),m_a22(a22),m_a23(a23),m_a31(a31),m_a32(a32),m_a33(a33),m_b1(b1),m_b2(b2),m_b3(b3),m_c1(c1),m_c2(c2),m_c3(c3),m_d(d)
{

}

double Discrete::update(double input)
{
    double output=getoutput();
    double tmp_x1=m_x1;
    double tmp_x2=m_x2;
    double tmp_x3=m_x3;
    m_x1=input*m_b1+tmp_x1*m_a11+tmp_x2*m_a12+tmp_x3*m_a13;
    m_x2=input*m_b2+tmp_x1*m_a21+tmp_x2*m_a22+tmp_x3*m_a23;
    m_x3=input*m_b3+tmp_x1*m_a31+tmp_x2*m_a12+tmp_x3*m_a33;

    m_previous_input=input;
    return output;
}

double Discrete::getoutput()
{
   return m_x1*m_c1+m_x2*m_c2+m_x3*m_c3+m_previous_input*m_d;
}
