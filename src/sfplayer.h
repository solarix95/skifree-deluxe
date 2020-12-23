#ifndef SFPLAYER_H
#define SFPLAYER_H

#include <QMap>
#include <QImage>
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

    virtual void keyPressEvent(QKeyEvent *event);
    virtual QRectF boundingRect() const;

  protected:
    virtual void renderModelCentered(QPainter &p) const;

private:
    QImage currentSprite() const;

    State              mState;
    QMap<State,QImage> mSprites;
};

#endif // SFPLAYER_H
