#ifndef QTR2DMENUSTYLE_H
#define QTR2DMENUSTYLE_H

#include <QColor>
#include <QPen>
#include <QBrush>

class Qtr2dMenuStyle : public QObject
{
public:
    Qtr2dMenuStyle();

    virtual int    border()       const = 0;
    virtual int    padding()      const = 0;
    virtual void   renderMenuBox(QPainter &p, const QSize &window) const = 0;
};

#endif // QTR2DMENUSTYLE_H
