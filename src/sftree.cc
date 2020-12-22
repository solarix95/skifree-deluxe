#include "sftree.h"

//-----------------------------------------------------------------
SfTree::SfTree(const SfSprites &sprites, const QPointF &p, Qtr2dZone &zone)
 : Qtr2dBody(p,zone)
{
}

//-----------------------------------------------------------------
QRectF SfTree::boundingRect() const
{
    return QRect(0,0,10,10);
}

//-----------------------------------------------------------------
void SfTree::renderModelCentered(QPainter &p) const
{
    p.setBrush(Qt::blue);
    p.drawLine(-10,-10,10,10);
}

