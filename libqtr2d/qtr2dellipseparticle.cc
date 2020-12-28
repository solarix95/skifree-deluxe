#include <QDebug>
#include "qtr2dellipseparticle.h"

//-------------------------------------------------------------------------------------------------
Qtr2dEllipseParticle::Qtr2dEllipseParticle(const QPointF &p, const QVector2D &dir, Qtr2dZone &zone, const QColor &c, int livetimeMs, float radius)
 : Qtr2dParticle(p, dir, zone, c, livetimeMs*0.5 + (qrand()%livetimeMs))
 , mRadius(radius)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dEllipseParticle::renderModelCentered(QPainter &p) const
{
    p.setPen(QPen(color(),0));
    p.setBrush(color());
    p.drawEllipse(QPointF(0,0),mRadius,mRadius);
}
