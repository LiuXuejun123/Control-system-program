#ifndef INTEGRATOR_H
#define INTEGRATOR_H

class Integrator
{
public:
    Integrator(double init_value);
    double update(double input,double dt);
    double state() const;

private:
    double m_state =0.0;
    double input_pre = 0.0;
};

#endif // INTEGRATOR_H
