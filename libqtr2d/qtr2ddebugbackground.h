#ifndef PXSDEBUGBACKGROUND_H
#define PXSDEBUGBACKGROUND_H

#include "qtr2dbackground.h"

class Qtr2dDebugBackground : public Qtr2dBackground
{
public:
    Qtr2dDebugBackground(QColor color, int raster, float penSize);

  protected:
    virtual void renderBkgnd(QPainter &p, const QRectF &window);

private:
    QColor mColor;
    int    mRaster;
    float  mPenSize;

};

#endif // PXSDEBUGBACKGROUND_H
