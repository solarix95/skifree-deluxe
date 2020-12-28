#ifndef PXSPARTICLE_H
#define PXSPARTICLE_H

#include <QTime>
#include "qtr2dobject.h"

class Qtr2dParticle : public Qtr2dObject
{
public:
    Qtr2dParticle(const QPointF &p, const QVector2D &dir, Qtr2dZone &zone, const QColor &color, int livetimeMs);

    virtual bool move(double speed) override;
    virtual QRectF boundingRect() const override;

protected:
    QColor color() const;
    float  progress() const;
    float  transparency() const;

private:
    QColor mColor;
    int    mLivetimeMs;
    QTime  mTime;
};

typedef QList<Qtr2dParticle*> PxsParticles;

#endif // PXSPARTICLE_H
