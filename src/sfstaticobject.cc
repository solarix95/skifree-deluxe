#include "sfstaticobject.h"

//-------------------------------------------------------------------------------------------------
SfStaticObject::SfStaticObject(const QPixmap &sprite, const QRect &collisionBox,
                               const QPointF &p, Qtr2dZone &zone)
 : Qtr2dBody(p,zone)
 , mSprite(sprite.toImage())
 , mCollisionBox(collisionBox)
{
}

//-------------------------------------------------------------------------------------------------
QRectF SfStaticObject::boundingRect() const
{
    int x = -mSprite.width()/2;
    int y =  mSprite.height()/2;

    QRect box(x,y,mSprite.width(),mSprite.height());
    return box.translated(pos().x(),pos().y());
}

//-------------------------------------------------------------------------------------------------
void SfStaticObject::renderModelCentered(QPainter &p) const
{
    int startX = -mSprite.width()/2;
    int startY =  mSprite.height()/2;

    int y = -mSprite.height()/2;

    QRgb white = QColor(Qt::white).rgb();
    for (int x=0; x<mSprite.width(); x++) {
        for (int y=0; y<mSprite.height(); y++) {
            QRgb c = mSprite.pixel(x,y);
            if (c == white)
                continue;
            p.setPen(QColor(c));
            p.drawPoint(startX+x, startY-y);
        }
    }
}

