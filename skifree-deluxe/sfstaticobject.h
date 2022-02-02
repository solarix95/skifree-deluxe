#ifndef SFSTATICOBJECT_H
#define SFSTATICOBJECT_H

#include <QPixmap>
#include <QRect>
#include <QImage>
#include <QPainterPath>
#include <qtr2dbody.h>


class SfStaticObject : public Qtr2dBody

{
public:
    SfStaticObject(const QPixmap &sprite, const QRect &collisionBox, // Skifree
                   const QPointF &p, Qtr2dZone &zone);               // libqtr2d


    virtual QRectF boundingRect() const;


protected:
    virtual void renderModelCentered(QPainter &p) const;

private:
    QImage       mSprite;
    QPainterPath mPainterPath;
    QRect        mCollisionBox;
};

#endif // SFSTATICOBJECT_H
