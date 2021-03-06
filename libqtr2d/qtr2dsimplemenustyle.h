#ifndef QTR2DSIMPLEMENUSTYLE_H
#define QTR2DSIMPLEMENUSTYLE_H

#include <QPen>
#include <QBrush>
#include <QPainter>
#include "qtr2dmenustyle.h"

class Qtr2dSimpleMenuStyle : public Qtr2dMenuStyle
{
public:
    Qtr2dSimpleMenuStyle(int padding, QPen border, QBrush background);

    virtual int    border()       const override;
    virtual int    padding()      const override;
    virtual void   renderMenuBox(QPainter &p, const QSize &window) const override;

private:
    int    mPadding;
    QPen   mBorder;
    QBrush mBackground;
};

#endif // QTR2DSIMPLEMENUSTYLE_H
