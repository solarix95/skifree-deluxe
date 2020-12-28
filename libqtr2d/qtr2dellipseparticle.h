#ifndef PXSELLIPSEPARTICLE_H
#define PXSELLIPSEPARTICLE_H

#include "qtr2dparticle.h"

class Qtr2dEllipseParticle : public Qtr2dParticle
{
public:
    Qtr2dEllipseParticle(const QPointF &p, const QVector2D &direction, Qtr2dZone &zone, const QColor &c, int livetimeMs, float radius);

protected:
    virtual void renderModelCentered(QPainter &p) const;

protected:
    float mRadius;

};

#endif // PXSELLIPSEPARTICLE_H
