#ifndef PXSBRUSHBACKGROUND_H
#define PXSBRUSHBACKGROUND_H

#include <QBrush>
#include "qtr2dbackground.h"

class Qtr2dBrushBackground : public Qtr2dBackground
{
public:
    Qtr2dBrushBackground(const QBrush &brush);

protected:
    virtual void renderBkgnd(QPainter &p, const QRectF &window);

private:
    QBrush mBrush;
};

#endif // PXSBRUSHBACKGROUND_H
