#include <QTimer>
#include "qtr2dcameraeffect.h"

//-------------------------------------------------------------------------------------------------
Qtr2dCameraEffect::Qtr2dCameraEffect(int fps)
{
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(update()));
    t->start(1000/fps);
    mTime.start();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCameraEffect::update()
{
    emit updateRequest();
}

//-------------------------------------------------------------------------------------------------
int Qtr2dCameraEffect::elapsedMs() const
{
    return mTime.elapsed();
}
