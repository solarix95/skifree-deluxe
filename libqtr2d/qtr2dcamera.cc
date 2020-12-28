#include <QDebug>
#include "qtr2dcamera.h"
#include "qtr2dzone.h"
#include "qtr2dcameraeffect.h"

//-------------------------------------------------------------------------------------------------
Qtr2dCamera::Qtr2dCamera(Qtr2dZone *zone, QObject *parent)
    : QObject(parent)
    , mZone(NULL)
    , mCenter(0,0)
    , mRotation(0)
    , mAspectMode(IgnoreAspectRatio)
    , mFieldOfViewMode(VirtualFov)
    , mAntialiasingEnabled(false)
{
    setZone(zone);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setProjectionRect(const QRect &projection)
{
    mProjectionRect = projection;
    setupWorldMatrix();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setZone(Qtr2dZone *zone)
{
    Q_ASSERT(!mZone);
    if (!zone)
        return;

    mZone = zone;
    setWindow(mZone->fieldSize());
    connect(mZone, SIGNAL(updateRequest()), this, SIGNAL(updateRequest()));
    connect(mZone, SIGNAL(fieldSizeChanged()), this, SLOT(onFieldSizeChange()));
    connect(mZone, SIGNAL(requestCameraEffect(Qtr2dCameraEffect*)), this, SLOT(appendEffect(Qtr2dCameraEffect*)));
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::lookTo(const QPointF &center)
{
    mCenter = center;
    setupWorldMatrix();
}


//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::rotate(float angle)
{
    mRotation = angle;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setWindow(const QSize &zoneRect)
{
    mTargetWindowRect = zoneRect;
    setupWorldMatrix();
    emit updateRequest();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::appendEffect(Qtr2dCameraEffect *e)
{
    connect(e, SIGNAL(destroyed(QObject*)), this, SLOT(effectDestroyed(QObject*)));
    connect(e, SIGNAL(updateRequest()), this, SLOT(setupWorldMatrix()));
    mEffects << e;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::render(QPainter &p)
{
    if (!mZone)
        return;

    p.save();

    if (mAntialiasingEnabled)
        p.setRenderHint(QPainter::Antialiasing,true);
    p.setMatrix(mMatrix);

    mZone->render(p, mCurrentWindowRect);

    p.restore();
}

//-------------------------------------------------------------------------------------------------
QPointF Qtr2dCamera::center() const
{
    return mCenter;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::keyPressEvent(QKeyEvent *event)
{
    if (mZone)
        mZone->keyPressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::keyReleaseEvent(QKeyEvent *event)
{
    if (mZone)
        mZone->keyReleaseEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setAspectMode(int mode)
{
    mAspectMode = (AspectRatioMode)mode;
    setupWorldMatrix();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setFieldOfViewMode(int mode)
{
    Q_ASSERT(mode >= VirtualFov);
    Q_ASSERT(mode <= NativeFov);
    mFieldOfViewMode = (FovMode)mode;
    setupWorldMatrix();

}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setAntialiasingEnabled(bool enabled)
{
    mAntialiasingEnabled = enabled;
    emit updateRequest();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::onFieldSizeChange()
{
    setWindow(mZone->fieldSize());
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::effectDestroyed(QObject *effect)
{
    mEffects.removeAll((Qtr2dCameraEffect*)effect);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setupWorldMatrix()
{
    if (mProjectionRect.isEmpty() || mTargetWindowRect.isEmpty())
        return;

    if (mFieldOfViewMode == NativeFov)
        mTargetWindowRect = mProjectionRect.size();

    switch(mAspectMode) {
    case IgnoreAspectRatio: {
        setupFullscreenMatrix(mProjectionRect,mTargetWindowRect);
    } break;
    case FitToScreen: {

    } break;
    case AutoHeigh: {
        QSize windowRect = mTargetWindowRect;
        windowRect.setHeight(mTargetWindowRect.width()*(mProjectionRect.height()/(qreal)mProjectionRect.width()));
        setupFullscreenMatrix(mProjectionRect,windowRect);
    } break;
    case AutoWidth: {
        QSize windowRect = mTargetWindowRect;
        windowRect.setWidth(mTargetWindowRect.height()*(mProjectionRect.width()/(qreal)mProjectionRect.height()));
        setupFullscreenMatrix(mProjectionRect,windowRect);
    } break;
    default: Q_ASSERT(0 && "not implemented");
    }

    foreach(Qtr2dCameraEffect *effect, mEffects)
        effect->process(mMatrix, QRectF(mCenter.x()-mTargetWindowRect.width()/2,
                                        mCenter.y()-mTargetWindowRect.height()/2,
                                        mTargetWindowRect.width(), mTargetWindowRect.height()));

    QMatrix invertedM = mMatrix.inverted();

    QRectF boundingScreenRect(mProjectionRect.topLeft()-QPointF(1,1),mProjectionRect.bottomRight()+QPointF(1,1));
    mCurrentWindowRect = invertedM.mapRect(boundingScreenRect); // QRectF((mProjectionRect.topLeft()-QPointF(1,1))*invertedM, (mProjectionRect.bottomRight() + QPointF(1,1)) * invertedM);

    emit updateRequest();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dCamera::setupFullscreenMatrix(const QRect &projectionRect, const QSize &windowRect)
{
    // Screen Coordinates
    mMatrix.reset();
    mMatrix.translate(projectionRect.x(), projectionRect.y());
    mMatrix.translate(0,projectionRect.height());
    qreal dx = projectionRect.width()/(qreal)windowRect.width();
    qreal dy = projectionRect.height()/(qreal)windowRect.height();
    mMatrix.scale(dx,-dy);

    // from now, we have to use logicacoordinates ..!

    mMatrix.translate(windowRect.width()/2.0,windowRect.height()/2);
    mMatrix.rotate(-mRotation);
    mMatrix.translate(-windowRect.width()/2.0,-windowRect.height()/2);

    QPointF moveVector = QPointF(windowRect.width()/2.0,windowRect.height()/2)-center();
    mMatrix.translate(moveVector.x(), moveVector.y());

    // p.setClipRect(0,0,windowRect.width(),windowRect.height());
}
