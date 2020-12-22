#ifndef SFTREE_H
#define SFTREE_H

#include <qtr2dbody.h>
#include <QVariantMap>

class SfSprites;
class SfTree : public Qtr2dBody
{
public:
    SfTree(const SfSprites &sprites, const QPointF &p, Qtr2dZone &zone);

     virtual QRectF boundingRect() const;

protected:
    virtual void renderModelCentered(QPainter &p) const;
private:
    QPixmap mTreeBitmap;
};

#endif // SFTREE_H
