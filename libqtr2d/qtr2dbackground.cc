#include "qtr2dbackground.h"

//-------------------------------------------------------------------------------------------------
Qtr2dBackground::Qtr2dBackground()
 : mZone(NULL)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBackground::setZone(const Qtr2dZone *zone)
{
    mZone = zone;
    Q_ASSERT(mZone);
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dBackground::testCollision(Qtr2dObject *) const
{
    return false;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBackground::render(QPainter &p, const QRectF &window)
{
    p.save();
    renderBkgnd(p, window);
    p.restore();
}

//-------------------------------------------------------------------------------------------------
const Qtr2dZone &Qtr2dBackground::zone() const
{
    Q_ASSERT(mZone);
    return *mZone;
}
