#include "qtr2dzone.h"
#include "qtr2ddebugbackground.h"

//-------------------------------------------------------------------------------------------------
Qtr2dDebugBackground::Qtr2dDebugBackground(QColor color, int raster, float pen)
 : Qtr2dBackground()
 , mColor(color)
 , mRaster(raster)
 , mPenSize(pen)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dDebugBackground::renderBkgnd(QPainter &p, const QRectF &window)
{
    p.setBrush(Qt::black);
    p.drawRect(window);
    p.setPen(QPen(mColor,mPenSize));
    p.drawRect(0,0,zone().fieldSize().width(),zone().fieldSize().height());

    int crossSize = qMax(mRaster/10,1);
    float dx = zone().fieldSize().width()/(float)mRaster;
    float dy = zone().fieldSize().height()/(float)mRaster;
    for (float x = dx; x < zone().fieldSize().width(); x += dx) {
        for (float y = dy; y < zone().fieldSize().height(); y += dy) {
            p.drawLine(x, y + crossSize, x, y - crossSize);
            p.drawLine(x-crossSize, y, x+crossSize, y);
        }
    }
}

