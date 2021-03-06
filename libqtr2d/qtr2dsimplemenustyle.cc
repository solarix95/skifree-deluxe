#include "qtr2dsimplemenustyle.h"

//-------------------------------------------------------------------------------------------------
Qtr2dSimpleMenuStyle::Qtr2dSimpleMenuStyle(int padding, QPen border, QBrush background)
 : Qtr2dMenuStyle()
 , mPadding(padding)
 , mBorder(border)
 , mBackground(background)
{
}

//-------------------------------------------------------------------------------------------------
int Qtr2dSimpleMenuStyle::border() const
{
    return mBorder.width();
}

//-------------------------------------------------------------------------------------------------
int Qtr2dSimpleMenuStyle::padding() const
{
    return mPadding;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dSimpleMenuStyle::renderMenuBox(QPainter &p, const QSize &window) const
{
    p.setPen(mBorder);
    p.setBrush(mBackground);
    p.drawRect(QRect(0,0, window.width()-mBorder.width(), window.height()-mBorder.width()));
}

