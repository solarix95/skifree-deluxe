#include "qtr2dmassattraction.h"

void Qtr2dMassAttraction::process(Qtr2dBodies &bodies, PxsParticles &)
{
    Qtr2dForce g;
    for (int i=0; i<bodies.count(); i++) {
        Qtr2dBody *o = bodies.at(i);
        for (int j=i+1; j<bodies.count(); j++) {
            g = bodies[j]->gravityTo(o);
            if (!g.isNull())
                o->addGravity(-g);

            g = o->gravityTo(bodies[j]);
            if (!g.isNull())
                bodies[j]->addGravity(-g);
        }
    }
}
