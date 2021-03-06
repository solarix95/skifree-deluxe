#ifndef QTR2DWIN311MENUSTYLE_H
#define QTR2DWIN311MENUSTYLE_H

#include <QPen>
#include <QBrush>
#include <QPainter>
#include "qtr2dmenustyle.h"

class Qtr2dWin311MenuStyle : public Qtr2dMenuStyle
{
public:
    Qtr2dWin311MenuStyle();

    virtual int    border()       const override;
    virtual int    padding()      const override;
    virtual void   renderMenuBox(QPainter &p, const QSize &window) const override;
};

#endif // QTR2DWIN311MENUSTYLE_H
