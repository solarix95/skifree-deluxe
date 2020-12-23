#include <QDebug>
#include <QKeyEvent>
#include "sfplayer.h"

//-------------------------------------------------------------------------------------------------
SfPlayer::SfPlayer(const QPointF &p, Qtr2dZone &zone)
 : Qtr2dBody(p,zone)
{
    mState = LeftState;
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
void SfPlayer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        mState = LeftState;
        setVelocity(QVector2D(-0.5, -0.5));
    }
    if (event->key() == Qt::Key_Right) {
        mState = RightState;
        setVelocity(QVector2D( 0.5, -0.5));
    }
    emit changed(this);
}

//-------------------------------------------------------------------------------------------------
QRectF SfPlayer::boundingRect() const
{
    const QImage &sprite = currentSprite();
    int x = -sprite.width()/2;
    int y =  sprite.height()/2;

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
QImage SfPlayer::currentSprite() const
{
    return mSprites[mState];
}

