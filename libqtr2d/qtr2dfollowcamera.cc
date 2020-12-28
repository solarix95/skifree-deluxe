#include "qtr2dobject.h"
#include "qtr2dfollowcamera.h"

//----------------------------------------------------------------------------------
Qtr2dFollowCamera::Qtr2dFollowCamera(Qtr2dZone *zone, QObject *parent)
 : Qtr2dCamera(zone,parent)
 , mFollowMe(NULL)
{
}

//----------------------------------------------------------------------------------
void Qtr2dFollowCamera::followObject(const Qtr2dObject *obj, Options options)
{
    if (mFollowMe)
        mFollowMe->disconnect(this);

    mFollowMe = obj;
    mOptions  = options;

    if (!mFollowMe)
        return;

    connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(objDestroyed(QObject*)));
    connect(obj, SIGNAL(changed(Qtr2dObject*)), this, SLOT(updateCam()));
    updateCam();
}

//----------------------------------------------------------------------------------
void Qtr2dFollowCamera::objDestroyed(QObject *obj)
{
    if (mFollowMe != obj)
        return;
    mFollowMe = NULL;
    updateCam();
}

//----------------------------------------------------------------------------------
void Qtr2dFollowCamera::updateCam()
{
    if (!mFollowMe)
        return;

    if (mOptions.testFlag(FollowPosition))
        lookTo(mFollowMe->pos());

    if (mOptions.testFlag(FollowAngle))
        rotate(mFollowMe->angle());
}
