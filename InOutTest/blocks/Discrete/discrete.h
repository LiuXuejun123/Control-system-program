#ifndef DISCRETE_H
#define DISCRETE_H


class Discrete
{
public:
    Discrete(double x1,double x2,double x3,
             double a11,double a12,double a13,
             double a21,double a22,double a23,
             double a31,double a32,double a33,
             double b1,double b2,double b3,
             double c1,double c2,double c3,double d);
    double getoutput();
    double update(double input);
private:
    //initial state
    double m_x1;
    double m_x2;
    double m_x3;
    // State matrix
    double m_a11;
    double m_a12;
    double m_a13;
    double m_a21;
    double m_a22;
    double m_a23;
    double m_a31;
    double m_a32;
    double m_a33;

    double m_b1;
    double m_b2;
    double m_b3;

    double m_c1;
    double m_c2;
    double m_c3;

    double m_d;
    double m_previous_input;
};

#endif // DISCRETE_H
