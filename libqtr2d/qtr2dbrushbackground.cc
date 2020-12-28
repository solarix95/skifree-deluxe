#include "qtr2dbrushbackground.h"

//-------------------------------------------------------------------------------------------------
Qtr2dBrushBackground::Qtr2dBrushBackground(const QBrush &brush)
 : mBrush(brush)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBrushBackground::renderBkgnd(QPainter &p, const QRectF &window)
{
    p.setBrush(mBrush);
    p.drawRect(window);
}

