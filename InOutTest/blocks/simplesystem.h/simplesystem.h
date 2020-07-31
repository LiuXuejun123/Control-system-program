#ifndef SIMPLESYSTEM_H
#define SIMPLESYSTEM_H
#include"blocks/integrator/integrator.h"

class simplesystem
{
public:
    simplesystem(double initvalue);
    double getoutput() const;
    double update(double value,double dt);
private:
   Integrator *m_integrator;
};

#endif // SIMPLESYSTEM_H
