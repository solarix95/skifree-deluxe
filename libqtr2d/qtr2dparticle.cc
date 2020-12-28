#include "qtr2dparticle.h"

//-------------------------------------------------------------------------------------------------
Qtr2dParticle::Qtr2dParticle(const QPointF &p, const QVector2D &dir, Qtr2dZone &zone, const QColor &color, int livetimeMs)
 : Qtr2dObject(p, zone)
 , mColor(color)
 , mLivetimeMs(livetimeMs)
{
    velocity() = dir;
    mTime.start();
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dParticle::move(double speed)
{
    if (mTime.elapsed() >= mLivetimeMs)
        deleteLater();
    return Qtr2dObject::move(speed);
}

//-------------------------------------------------------------------------------------------------
QRectF Qtr2dParticle::boundingRect() const
{
    return QRectF();
}

//-------------------------------------------------------------------------------------------------
QColor Qtr2dParticle::color() const
{
    QColor c = mColor;
    c.setAlphaF(1-progress());
    return c;
}

//-------------------------------------------------------------------------------------------------
float Qtr2dParticle::progress() const
{
    return qMin(mTime.elapsed()/(float)mLivetimeMs,1.0f);
}

//-------------------------------------------------------------------------------------------------
float Qtr2dParticle::transparency() const
{
    return 0;

}
