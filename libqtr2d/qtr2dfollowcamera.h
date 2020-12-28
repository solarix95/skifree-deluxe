#ifndef PXSFOLLOWCAMERA_H
#define PXSFOLLOWCAMERA_H

#include <QFlags>
#include "qtr2dcamera.h"

class Qtr2dObject;
class Qtr2dFollowCamera : public Qtr2dCamera
{
    Q_OBJECT
public:
    enum Option {
        NoOptions      = 0x00,
        FollowPosition = 0x01,
        FollowAngle    = 0x02
    };
    Q_DECLARE_FLAGS(Options, Option)

    Qtr2dFollowCamera(Qtr2dZone *zone = NULL, QObject *parent = NULL);

public slots:
    void followObject(const Qtr2dObject *obj,Options options = FollowPosition);

private slots:
    void objDestroyed(QObject *obj);
    void updateCam();

private:
    Options          mOptions;
    const Qtr2dObject *mFollowMe;
};

#endif // PXSFOLLOWCAMERA_H
