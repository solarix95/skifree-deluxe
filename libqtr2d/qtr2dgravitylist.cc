#include "qtr2dgravitylist.h"

//-------------------------------------------------------------------------------------------------
Qtr2dGravityList::Qtr2dGravityList(const Qtr2dForces &forces)
 : mForces(forces)
{
}

//-------------------------------------------------------------------------------------------------
Qtr2dGravityList::Qtr2dGravityList(const Qtr2dForce &force)
 : mForces(Qtr2dForces() << force)
{
}

void Qtr2dGravityList::process(Qtr2dBodies &bodies, PxsParticles &)
{
    if (mForces.isEmpty())
        return;
    for (int i=0; i<bodies.count(); i++) {
        foreach (const Qtr2dForce &f, mForces) {
            bodies.at(i)->addGravity(f);
        }
    }
}
