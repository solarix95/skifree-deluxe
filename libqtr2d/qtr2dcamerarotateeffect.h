#ifndef PXSCAMERAROTATEEFFECT_H
#define PXSCAMERAROTATEEFFECT_H

#include "qtr2dcameraeffect.h"

class Qtr2dCameraRotateEffect : public Qtr2dCameraEffect
{
public:
    Qtr2dCameraRotateEffect(int durationMs);

    virtual void process(QMatrix &matrix, const QRectF &window) override;

private:
    QTime mTime;
    int   mDurationMs;
};

#endif // PXSCAMERAROTATEEFFECT_H
