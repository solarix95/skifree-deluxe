#include "sfautoplayer.h"
#include <QTimer>

SfAutoPlayer::SfAutoPlayer(const QPointF &p, Qtr2dZone &zone)
 : SfPlayer(p, zone)
{
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [&]() {
        if (state() != CrashedState)
            setState(qrand() % 2 ? LeftState : RightState);
    });

    t->start(1000);
}
