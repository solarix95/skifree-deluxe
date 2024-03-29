#include <QDebug>
#include <QKeyEvent>

#include <qtr2dzone.h>

#include "sfplayer.h"

//-------------------------------------------------------------------------------------------------
SfPlayer::SfPlayer(const QPointF &p, Qtr2dZone &zone)
 : Qtr2dBody(p,zone)
 , mSpeed(0.5)
 , mJumpHeight(0)
 , mJumpStep(0)
{
    mState     = LeftState;
    mGroundPos = pos();
    mCollisionRadius = 50;
    mCollisionType   = RectCollision;
}

//-------------------------------------------------------------------------------------------------
SfPlayer::~SfPlayer()
{
}

//-------------------------------------------------------------------------------------------------
void SfPlayer::appendSprite(SfPlayer::State s, const QPixmap &sprite)
{
    if (sprite.isNull())
        return;

    mSprites[s] = sprite.toImage();
}

//-------------------------------------------------------------------------------------------------
void SfPlayer::setSpeed(float speed)
{
    mSpeed = speed;
}

//-------------------------------------------------------------------------------------------------
bool SfPlayer::move(double speed)
{
    if (mState == CrashedState && mStateTimer.elapsed() > 2000) {
        // Repositioning after Crash:
        do {
            mGroundPos = QPointF(mGroundPos.x(),mGroundPos.y() - 50);
            updatePosition(mGroundPos);
        } while (testCollision(true));

        setState(qrand()%2 ? LeftState : RightState);
        setState(DownHillState); // will be ignored if there is no downhill..
        return false;
    }

    accelerate(speed);
    mGroundPos = QPointF(mGroundPos.x() + velocity().x(),mGroundPos.y() + velocity().y());

    if (mJumpStep > 0) {
        mJumpHeight += mJumpStep * speed;
        mJumpStep -= 0.2;
    }

    if (mJumpHeight < 0) {
        mJumpHeight = 0;
        mJumpStep   = 0;
        setState(DownHillState);
    }

    QPointF newPos(mGroundPos.x(), mGroundPos.y() + mJumpHeight);
    updatePosition(newPos);
    testCollision();


    if (!velocity().isNull())
        zone().createParticles(collisionRect().translated(0,5),-velocity(),1,0.5,Qt::gray,250);
    return false;
}


//-------------------------------------------------------------------------------------------------
void SfPlayer::keyPressEvent(QKeyEvent *event)
{
    if (mState == CrashedState)
        return;

    if (event->key() == Qt::Key_Left) {
        setState(LeftState);
    }
    if (event->key() == Qt::Key_Right) {
        setState(RightState);
    }
    if (event->key() == Qt::Key_Down) {
        setState(DownHillState);
    }

    if (event->key() == Qt::Key_Space && mJumpHeight <= 0) {
        mJumpStep = 2 + 0.5*(velocity().y()*velocity().y());
        qDebug() << mJumpStep;
    }
    emit changed(this);
}

//-------------------------------------------------------------------------------------------------
QRectF SfPlayer::boundingRect() const
{
    const QImage &sprite = currentSprite();
    int x = -sprite.width()/2;
    int y = -sprite.height()/2;

    QRect box(x,y,sprite.width(),sprite.height());
    return box.translated(pos().x(),pos().y());
}

//-------------------------------------------------------------------------------------------------
void SfPlayer::renderModelCentered(QPainter &p) const
{
    const QImage &sprite = currentSprite();

    int startX = -sprite.width()/2;
    int startY =  sprite.height()/2;


    QRgb white = QColor(Qt::white).rgb();

    for (int x=0; x<sprite.width(); x++) {
        for (int y=0; y<sprite.height(); y++) {
            QRgb c = sprite.pixel(x,y);
            if (c == white)
                continue;
            p.setPen(QColor(c));
            p.drawPoint(startX+x, startY-y);
        }
    }
}

//-------------------------------------------------------------------------------------------------
void SfPlayer::onCollision(Qtr2dBody *other)
{
    setState(CrashedState);
}

//-------------------------------------------------------------------------------------------------
SfPlayer::State SfPlayer::state() const
{
    return mState;
}

//-------------------------------------------------------------------------------------------------
QImage SfPlayer::currentSprite() const
{
    return mSprites[mState];
}

//-------------------------------------------------------------------------------------------------
void SfPlayer::setState(SfPlayer::State newState)
{
    if (mState == newState)
        return;

    if (!mSprites.contains(newState))
        return;

    mState = newState;
    mStateTimer.start();

    // on new state:
    switch(mState) {
    case CrashedState:
        setVelocity(QVector2D(0,0));
        break;
    case LeftState:
        setVelocity(QVector2D(-mSpeed, -mSpeed));
        break;
    case RightState:
        setVelocity(QVector2D( mSpeed, -mSpeed));
        break;
    case DownHillState:
        setVelocity(QVector2D( 0, -1.5 * mSpeed));
        break;
    }
}

