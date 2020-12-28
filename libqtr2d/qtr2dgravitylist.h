#ifndef PXSGRAVITYLIST_H
#define PXSGRAVITYLIST_H

#include "qtr2dbasetypes.h"
#include "qtr2dgravity.h"

class Qtr2dGravityList : public Qtr2dGravity
{
public:
    Qtr2dGravityList(const Qtr2dForces &forces);
    Qtr2dGravityList(const Qtr2dForce &force);
    virtual void process(Qtr2dBodies &bodies, PxsParticles &particles) override;

    inline Qtr2dForces &forces() { return mForces; }

private:

    Qtr2dForces mForces;

};

#endif // PXSGRAVITYLIST_H
