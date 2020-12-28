#include <QTimer>
#include <QDebug>
#include "qtr2dcamerashakeeffect.h"

inline float randomizeFloat(float v)
{
    return v*((-50 + qrand()%100)/50.0);
}

//-------------------------------------------------------------------------------------------------
Qtr2dCameraShakeEffect::Qtr2dCameraShakeEffect(float ax, float ay, float az, float rot, int durationMs)
    : Qtr2dCameraEffect(30)
    , mAx(ax)
    , mAy(ay)
    , mAz(az)
    , mRotation(rot)
    , mDuration(durationMs)
{
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(deleteLater()));
    t->start(durationMs);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCameraShakeEffect::process(QMatrix &matrix, const QRectF &window)
{
    Q_UNUSED(window);
    float prog = progress();
    matrix.translate(randomizeFloat(mAx*prog),
                     randomizeFloat(mAy*prog));

    matrix.rotate(randomizeFloat(mRotation*prog));
}

//-------------------------------------------------------------------------------------------------
float Qtr2dCameraShakeEffect::progress() const
{
    return qMax((mDuration-elapsedMs())/(float)mDuration,0.0f);
}
