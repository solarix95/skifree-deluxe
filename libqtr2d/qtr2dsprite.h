#ifndef QTR2DSPRITE_H
#define QTR2DSPRITE_H

#include <QPixmap>
#include <QPainter>

class Qtr2dSprite
{
public:
    Qtr2dSprite(const QPixmap &pixmap);

    void renderCentered(QPainter &p);

private:
    QPixmap mPixmap;

};

#endif // QTR2DSPRITE_H
