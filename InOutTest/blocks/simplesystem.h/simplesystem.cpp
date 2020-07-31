#include "simplesystem.h"

simplesystem::simplesystem(double initvalue)
{
    m_integrator=new Integrator(initvalue);
}

double simplesystem::getoutput() const
{
    return m_integrator->state();
}

double simplesystem::update(double value, double dt)
{
    double tmp=m_integrator->state();
    m_integrator->update(value-tmp,dt);
    return tmp;
}
