#include "qtr2dmenu.h"

//-------------------------------------------------------------------------------------------------
Qtr2dMenu::Qtr2dMenu(Qtr2dMenuStyle &style, QObject *parent)
  : QObject(parent)
  , mStyle(style)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dMenu::keyEvent(QKeyEvent *event)
{
    if (event->type() == QEvent::KeyPress)
        keyPressEvent(event);
    if (event->type() == QEvent::KeyRelease)
        keyReleaseEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dMenu::render(QPainter &p, const QRect &window)
{
    p.translate(window.topLeft());
    renderBox(p,window.size());
    p.setClipRect(0,0,window.size().width(),window.size().height());

    renderContent(p,window.size());
}

//-------------------------------------------------------------------------------------------------
void Qtr2dMenu::renderBox(QPainter &p, const QSize &boxSize)
{
    p.save();
    style().renderMenuBox(p,boxSize);
    p.restore();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dMenu::keyPressEvent(QKeyEvent *)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dMenu::keyReleaseEvent(QKeyEvent *)
{
}

//-------------------------------------------------------------------------------------------------
const Qtr2dMenuStyle &Qtr2dMenu::style() const
{
    return mStyle;
}


