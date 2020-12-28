#ifndef PXS_BODY_H
#define PXS_BODY_H

#include <QPainter>
#include <QObject>
#include <QPointF>
#include <QKeyEvent>
#include <QList>
#include <QVector2D>
#include "qtr2dobject.h"
#include "qtr2dbasetypes.h"

class Qtr2dBody : public Qtr2dObject
{
    Q_OBJECT
public:
    explicit Qtr2dBody(const QPointF &p, Qtr2dZone &zone);

    virtual void     addGravity(const Qtr2dForce &f);
    virtual bool     move(double speed);
    virtual Qtr2dForce gravityTo(Qtr2dBody *other) const;

    // Input Events
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    virtual void accelerate(double speed);
    virtual void testCollision();
    virtual void testCollision(Qtr2dBody *other);

    void collideWith(Qtr2dBody *other);
    virtual void onCollision(Qtr2dBody *other);

    virtual Qtr2dForce collectForces() const;

    Qtr2dForce  mGravity;
    float     mAcceleration;
    float     mMass;

    enum CollisionType {
        RectCollision,
        RadialCollision,
    };

    CollisionType mCollisionType;
    float         mCollisionRadius;
};

typedef QList<Qtr2dBody*> Qtr2dBodies;

#endif
