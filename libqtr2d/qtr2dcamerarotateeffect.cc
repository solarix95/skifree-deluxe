#include <QDebug>
#include "qtr2dcamerarotateeffect.h"

Qtr2dCameraRotateEffect::Qtr2dCameraRotateEffect(int durationMs)
{
    mDurationMs = durationMs;
    mTime.start();
}

void Qtr2dCameraRotateEffect::process(QMatrix &matrix, const QRectF &window)
{
    float progress = mTime.elapsed()/(float)mDurationMs;
    matrix.translate(window.center().x(), window.center().y());
    matrix.rotate(progress*360);
    matrix.translate(-window.center().x(), -window.center().y());
    if (mTime.elapsed() > mDurationMs)
        deleteLater();
}
