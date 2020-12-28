#ifndef PXSMASSATTRACTION_H
#define PXSMASSATTRACTION_H

#include "qtr2dgravity.h"

class Qtr2dMassAttraction : public Qtr2dGravity
{
public:
    virtual void process(Qtr2dBodies &bodies, PxsParticles &particles);

};

#endif // PXSMASSATTRACTION_H
