#include <QDebug>
#include "qtr2dpolygonbody.h"

//-------------------------------------------------------------------------------------------------
Qtr2dPolygonBody::Qtr2dPolygonBody(const QPointF &p, Qtr2dZone &zone)
 : Qtr2dBody(p, zone)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dPolygonBody::setPolygons(const Qtr2dPolygonBody::Polygons &polygons)
{
    mPolygons     = polygons;
    mBoundingTopLeft = mBoundingBottomRight = QPointF();
    if (mPolygons.isEmpty())
        return;

    // Update Bounding Rect..
    QPointF topLeft, bottomRight;
    topLeft = bottomRight = mPolygons.first().points.first();
    foreach (const Polygon &polygon, mPolygons) {
        foreach(const QPointF &point, polygon.points) {
            if (point.x() < topLeft.x())
                topLeft.setX(point.x());
            if (point.y() > topLeft.y())
                topLeft.setY(point.y());
            if (point.x() > bottomRight.x())
                bottomRight.setX(point.x());
            if (point.y() < bottomRight.y())
                bottomRight.setY(point.y());
        }
    }

    mBoundingTopLeft     = topLeft;
    mBoundingBottomRight = bottomRight;
}

//-------------------------------------------------------------------------------------------------
QRectF Qtr2dPolygonBody::boundingRect() const
{
    float height = mBoundingTopLeft.y() - mBoundingBottomRight.y();
    float width  = mBoundingBottomRight.x() - mBoundingTopLeft.x();
    // qDebug() << QRectF(pos() + mBoundingTopLeft, pos() + mBoundingBottomRight);
    return QRectF(pos() + mBoundingTopLeft, QSizeF(width, -height));
}

//-------------------------------------------------------------------------------------------------
void Qtr2dPolygonBody::renderModelCentered(QPainter &p) const
{
    foreach (const Polygon &polygon, mPolygons) {
        p.setPen(polygon.pen);
        p.setBrush(polygon.brush);
        p.drawPolygon(polygon.points.constData(),polygon.points.count());
    }
}
