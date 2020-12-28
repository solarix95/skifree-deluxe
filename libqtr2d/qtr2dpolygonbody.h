#ifndef PXSPOLYGONBODY_H
#define PXSPOLYGONBODY_H

#include <QVector>
#include <QPointF>
#include <QBrush>
#include <QPen>
#include "qtr2dbody.h"


class Qtr2dPolygonBody : public Qtr2dBody
{
public:
    typedef QVector<QPointF> Points;
    struct Polygon {
        QPen             pen;
        QBrush           brush;
        Points           points;
        Polygon(QPen p, QBrush b, const Points &pts)
            : pen(p), brush(b), points(pts) {}
    };
    typedef QList<Polygon> Polygons;

    Qtr2dPolygonBody(const QPointF &p, Qtr2dZone &zone);

    void setPolygons(const Polygons &polygons);
    virtual QRectF   boundingRect() const override;

protected:
    virtual void renderModelCentered(QPainter &p) const override;

private:
    Polygons    mPolygons;
    QPointF     mBoundingTopLeft;
    QPointF     mBoundingBottomRight;
};

#endif // PXSPOLYGONBODY_H
