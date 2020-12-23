#include <QDebug>
#include <QKeyEvent>
#include "sfplayer.h"

//-------------------------------------------------------------------------------------------------
SfPlayer::SfPlayer(const QPointF &p, Qtr2dZone &zone)
 : Qtr2dBody(p,zone)
{
    mState = LeftState;
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
    mSprites[s] = sprite.toImage();
}

//-------------------------------------------------------------------------------------------------
bool SfPlayer::move(double speed)
{
    if (mState == CrashedState && mStateTimer.elapsed() > 1000) {

    }

    return Qtr2dBody::move(speed);
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
QImage SfPlayer::currentSprite() const
{
    return mSprites[mState];
}

//-------------------------------------------------------------------------------------------------
void SfPlayer::setState(SfPlayer::State newState)
{
    if (mState == newState)
        return;

    mState = newState;
    mStateTimer.start();

    // on new state:
    switch(mState) {
    case CrashedState:
        setVelocity(QVector2D(0,0));
        break;
    case LeftState:
        setVelocity(QVector2D(-0.5, -0.5));
        break;
    case RightState:
        setVelocity(QVector2D( 0.5, -0.5));
        break;
    }
}

