#ifndef PXSGRAVITY_H
#define PXSGRAVITY_H

#include "qtr2dbody.h"
#include "qtr2dparticle.h"

class Qtr2dGravity
{
public:
    virtual ~Qtr2dGravity();
    virtual void process(Qtr2dBodies &bodies, PxsParticles &particles) = 0;
};

#endif // PXSGRAVITY_H
