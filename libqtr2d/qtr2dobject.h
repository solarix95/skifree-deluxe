#ifndef PXS_OBJECT_H
#define PXS_OBJECT_H

#include <QPainter>
#include <QObject>
#include <QPointF>
#include <QList>
#include <QVector2D>

class Qtr2dZone;
class Qtr2dObject : public QObject
{
    Q_OBJECT
public:
    explicit Qtr2dObject(const QPointF &p, Qtr2dZone &zone);

    void   render(QPainter &p) const;

    inline const   QPointF  &pos() const      { return mPos;      }
    inline void              setPos(const QPointF &p) { mPos = p; }
    inline const QVector2D  &velocity() const { return mVelocity; }
    inline void              setVelocity(const QVector2D &v) { mVelocity = v; }
    inline float             angle() const     { return mAngle; }
    inline void              setAngle(float a) { mAngle = a;    }
    inline void              setSpin(float s)  { mSpin  = s;    }
    inline float             distanceTo(const Qtr2dObject &oth) const { return (mPos-oth.mPos).manhattanLength(); }

    virtual bool   move(double speed);
    virtual QRectF boundingRect() const = 0;
    virtual QRectF collisionRect() const;

signals:
    void changed(Qtr2dObject *obj);
    void created(Qtr2dObject *childObj);

protected:
    virtual void renderModelCentered(QPainter &p) const = 0;
    virtual void updatePosition(const QPointF &newPos);

    inline float     &spin()     { return mSpin;  }
    inline float     &angle()    { return mAngle; }
    inline Qtr2dZone   &zone()     { return mZone;  }
    inline QVector2D &velocity() { return mVelocity; }

private:
    QPointF   mPos;
    Qtr2dZone  &mZone;
    QVector2D mVelocity;
    float     mAngle; // current angle
    float     mSpin;
};

typedef QList<Qtr2dObject*> PxsObjects;

#endif // SPACEOBJECT_H
