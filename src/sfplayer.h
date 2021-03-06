#ifndef SFPLAYER_H
#define SFPLAYER_H

#include <QMap>
#include <QImage>
#include <QTime>
#include <qtr2dbody.h>


class SfPlayer : public Qtr2dBody
{
public:
    enum State {
        LeftState,
        RightState,
        CrashedState
    };

    SfPlayer(const QPointF &p, Qtr2dZone &zone);
    virtual ~SfPlayer();

    void appendSprite(State s, const QPixmap &sprite);
    void setSpeed(float speed);
    void setState(State newState);

    virtual bool     move(double speed);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual QRectF boundingRect() const;

  protected:
    virtual void renderModelCentered(QPainter &p) const;
    virtual void onCollision(Qtr2dBody *other);

private:
    QImage currentSprite() const;

    float              mSpeed;
    float              mJumpHeight;
    float              mJumpStep;
    QPointF            mGroundPos;
    State              mState;
    QTime              mStateTimer;
    QMap<State,QImage> mSprites;
};

#endif // SFPLAYER_H
