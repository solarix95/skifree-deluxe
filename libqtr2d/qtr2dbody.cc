#include "qtr2dbody.h"
#include "qtr2dzone.h"
#include <QDebug>


//-------------------------------------------------------------------------------------------------
Qtr2dBody::Qtr2dBody(const QPointF &p, Qtr2dZone &zone)
    : Qtr2dObject(p, zone)
    , mAcceleration(0.0)
    , mMass(0)
    , mCollisionType(RectCollision)
    , mCollisionRadius(0)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBody::addGravity(const Qtr2dForce &f)
{
    mGravity.setX(mGravity.x() + f.x());
    mGravity.setY(mGravity.y() + f.y());
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dBody::move(double speed)
{
    angle() += spin()*speed;

    accelerate(speed);
    velocity().setX(velocity().x() + mGravity.x());
    velocity().setY(velocity().y() + mGravity.y());

    QPointF newPos(pos().x() + velocity().x(),pos().y() + velocity().y());
    updatePosition(newPos);
    testCollision();

    mGravity = Qtr2dForce(0,0);
    return false;
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dBody::testCollision(bool test)
{
    bool collision = false;
    foreach(Qtr2dBody *other, zone().bodies()) {
        if (other != this)
            collision = other->testCollision(this, test) || collision;
    }
    if (zone().testCollision(this)) {
        collision = true;
        if (!test)
            collideWith(NULL);
    }

    return collision;
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dBody::testCollision(Qtr2dBody *other, bool test)
{
    Q_ASSERT(this != other);
    if (QVector2D(this->pos() - other->pos()).length() > (this->mCollisionRadius + other->mCollisionRadius))
        return false;

    // Rect/Rect Collision
    if (this->mCollisionType == RectCollision && other->mCollisionType == RectCollision) {
        if (this->collisionRect().intersects(other->collisionRect()))
        {
            if (!test)
                this->collideWith(other);
            return true;
        }
        return false;
    }

    // Radial/Radial
    if (this->mCollisionType == RadialCollision && other->mCollisionType == RadialCollision) {
        if (!test)
            this->collideWith(other);
        return true;
    }

    // TODO: Rect/Radial-Collision
    // Rect/Radial
    Qtr2dBody *rectBody  = this->mCollisionType == RectCollision ? this : other;
    Qtr2dBody *radialBody = rectBody == this ? other : this;

    return false;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBody::collideWith(Qtr2dBody *other)
{
    Q_ASSERT(this != other);
    this->onCollision(other);

    if (other)
        other->onCollision(this);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBody::onCollision(Qtr2dBody *)
{
}

//-------------------------------------------------------------------------------------------------
Qtr2dForce Qtr2dBody::collectForces() const
{
    /*
    PxsForces f;
    QMatrix m;
    m.translate(0,mAcceleration);
    m.rotate(mAngle);

    f << PxsForce(m.dx(),m.dy());
    */
    Qtr2dForce next;
    return next;
    /*
    foreach(PxsBody *other, mFriends) {
        if (other == this)
            continue;
        next = other->gravityTo(this);
        if (!next.isNull())
            f << next;
    }

    return f;
    */
}

//-------------------------------------------------------------------------------------------------
Qtr2dForce Qtr2dBody::gravityTo(Qtr2dBody *other) const
{
    if (this == other)
        return Qtr2dForce();

    QPointF v = other->pos() - this->pos();
    Qtr2dForce f(v.x(),v.y());
    float d = f.length();
    float g = this->mMass/(d*d);
    // float g = qMin(this->mMass/(d*d),.5f);
    f.normalize();
    f *= g;
    return f;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBody::keyPressEvent(QKeyEvent*)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBody::keyReleaseEvent(QKeyEvent *)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dBody::accelerate(double speed)
{
    if (!mAcceleration)
        return;
    QMatrix m;
    m.rotate(angle());
    QPointF acc(0,mAcceleration*speed);
    acc = acc * m;

    velocity().setX(velocity().x() + acc.x());
    velocity().setY(velocity().y() + acc.y());
    emit changed(this);
}
