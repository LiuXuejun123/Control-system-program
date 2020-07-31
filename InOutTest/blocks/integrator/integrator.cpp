#include "integrator.h"

Integrator::Integrator(double init_value):m_state(init_value)
{

}

double Integrator::update(double input, double dt)
{
    m_state += (input+input_pre)*dt/2.0;
    input_pre = input;
    return m_state;
}

double Integrator::state() const
{
    return m_state;
}

