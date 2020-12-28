#ifndef PXSBACKGROUND_H
#define PXSBACKGROUND_H

#include <QObject>
#include <QPainter>

class Qtr2dZone;
class Qtr2dObject;
class Qtr2dBackground : public QObject
{
    Q_OBJECT
public:
    Qtr2dBackground();

    virtual void setZone(const Qtr2dZone *zone);
    virtual bool testCollision(Qtr2dObject *bdy) const;

    void render(QPainter &p, const QRectF &window);

signals:
    void updateRequest();

protected:
    const Qtr2dZone &zone() const;
    virtual void renderBkgnd(QPainter &p, const QRectF &window) = 0;

private:
    const Qtr2dZone *mZone;
};

#endif // PXSBACKGROUND_H
