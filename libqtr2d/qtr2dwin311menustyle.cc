#include "qtr2dwin311menustyle.h"

#define WIN311_BORDER  4
#define WIN311_CORNER 23

//-------------------------------------------------------------------------------------------------
Qtr2dWin311MenuStyle::Qtr2dWin311MenuStyle()
{

}

//-------------------------------------------------------------------------------------------------
int Qtr2dWin311MenuStyle::border() const
{
    return 5;
}

//-------------------------------------------------------------------------------------------------
int Qtr2dWin311MenuStyle::padding() const
{
    return 10;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWin311MenuStyle::renderMenuBox(QPainter &p, const QSize &window) const
{
    p.fillRect(QRect(0,0,window.width(),window.height()),Qt::white);
    p.setPen(QPen(QColor("#c0c0c0"),4));
    p.drawRect(QRect(2,2,window.width()-4,window.height()-4));

    p.setPen(QPen(Qt::black,1));
    p.drawRect(QRect(0,0,window.width(),window.height()));
    p.drawRect(QRect(4,4,window.width()-9,window.height()-9));

    // Topleft, Lower
    p.drawLine(0,WIN311_CORNER,
               WIN311_BORDER,WIN311_CORNER);
    // Topleft, Right
    p.drawLine(WIN311_CORNER,0,
               WIN311_CORNER,WIN311_BORDER);


    // TopRight, Lower
    p.drawLine(window.width()-WIN311_BORDER,WIN311_CORNER,
               window.width(),WIN311_CORNER);
    // TopRight, Left
    p.drawLine(window.width()-WIN311_CORNER,0,
               window.width()-WIN311_CORNER,WIN311_BORDER);

    // BottomLeft, Upper
    p.drawLine(0,window.height()-WIN311_CORNER,
               WIN311_BORDER,window.height()-WIN311_CORNER);
    // BottomLeft, Right
    p.drawLine(WIN311_CORNER,window.height()-WIN311_BORDER,
               WIN311_CORNER,window.height());

}
