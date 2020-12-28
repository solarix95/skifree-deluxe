#include "qtr2dobject.h"
#include <QDebug>

//-------------------------------------------------------------------------------------------------
Qtr2dObject::Qtr2dObject(const QPointF &p, Qtr2dZone &zone)
    : QObject(NULL)
    , mPos(p)
    , mZone(zone)
    , mAngle(0)
    , mSpin(0)
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dObject::render(QPainter &p) const
{
    p.save();

    p.translate(mPos);
    p.rotate(mAngle);

    renderModelCentered(p);

    p.restore();

    /* Debug */
    /*
    p.save();
    p.setBrush(Qt::transparent);
    p.setPen(QPen(Qt::blue,0.3));
    p.drawRect(boundingRect());
    p.setPen(QPen(Qt::green,0.3));
    p.drawRect(collisionRect());
    p.setPen(QPen(Qt::red,2.0));
    p.drawPoint(collisionRect().topLeft());
    p.restore();
    */
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dObject::move(double speed)
{
    if (mSpin)
        mAngle += mSpin*speed;

    if (mVelocity.x())
        mPos.setX(mPos.x() + mVelocity.x());

    if (mVelocity.y())
        mPos.setY(mPos.y() + mVelocity.y());

    emit changed(this);
    return false;
}

//-------------------------------------------------------------------------------------------------
QRectF Qtr2dObject::collisionRect() const
{
    QRectF br = boundingRect();

    float  paddingWidth  = br.width() * 0.1;
    float  paddingHeight = br.height() * 0.1;

    return QRectF(br.x() + paddingWidth, br.y() + paddingHeight,
                  br.width() - 2*paddingWidth,
                  br.height() - 2*paddingHeight);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dObject::updatePosition(const QPointF &newPos)
{
    if (mPos == newPos)
        return;
    mPos = newPos;
    emit changed(this);
}

/*
//-------------------------------------------------------------------------------------------------
void PxsObject::testCollision()
{
    foreach(SpaceObject *other, mFriends) {
        if (other != this)
            other->testCollision(this);
    }
}

//-------------------------------------------------------------------------------------------------
void PxsObject::testCollision(SpaceObject *other)
{
    Q_ASSERT(this != other);
    if (this->boundingRect().intersects(other->boundingRect())) {
        this->collideWith(other);
        other->collideWith(this);
    }
}

//-------------------------------------------------------------------------------------------------
Forces SpaceObject::collectForces() const
{
    Forces f;
    QMatrix m;
    m.translate(0,mAcceleration);
    m.rotate(mAngle);

    f << Force(m.dx(),m.dy());
    Force next;
    foreach(SpaceObject *other, mFriends) {
        if (other == this)
            continue;
        next = other->gravityTo(this);
        if (!next.isNull())
            f << next;
    }

    return f;
}

//-------------------------------------------------------------------------------------------------
Force SpaceObject::gravityTo(SpaceObject *other) const
{
    Q_ASSERT(this != other);

    QPointF v = other->mPos - this->mPos;
    Force f(v.x(),v.y());
    float d = f.length();
    float g = (other->mMass + this->mMass)/(d*d);

    f.normalize();
    f *= g;
    return f;
}
*/
