#ifndef PXS_CAMERA_H
#define PXS_CAMERA_H

#include <QPainter>
#include <QObject>
#include <QSizeF>
#include <QPointF>
#include <QMatrix>
#include <QKeyEvent>

class Qtr2dZone;
class Qtr2dCameraEffect;
class Qtr2dCamera : public QObject
{
    Q_OBJECT
public:
    enum AspectRatioMode {
        IgnoreAspectRatio, // Fit to Widget
        FitToScreen,
        AutoWidth,         // Calculate windowRect.width()
        AutoHeigh          // Calculate windowRect.height();
    };

    enum FovMode {
        VirtualFov,        // Free camera window
        NativeFov          // projectionRect == windowRect
    };

    explicit Qtr2dCamera(Qtr2dZone *zone = NULL, QObject *parent = NULL);

    void    setProjectionRect(const QRect &projection);
    void    render(QPainter &p);
    QPointF center() const;

    void  keyPressEvent(QKeyEvent *event);
    void  keyReleaseEvent(QKeyEvent *event);

signals:
    void updateRequest();

public slots:
    void setAspectMode(int mode);
    void setFieldOfViewMode(int mode);
    void setAntialiasingEnabled(bool enabled);
    void setZone(Qtr2dZone *zone);
    void lookTo(const QPointF &center);
    void rotate(float angle);
    void setWindow(const QSize &windowRect);
    void appendEffect(Qtr2dCameraEffect *e);

    // Aliases
    inline void lookTo(float x, float y) { lookTo(QPointF(x,y)); }

private slots:
    void onFieldSizeChange();
    void effectDestroyed(QObject *effect);
    void setupWorldMatrix();

private:
    void setupFullscreenMatrix(const QRect &projectionRect, const QSize &windowRect);

    Qtr2dZone        *mZone;
    QPointF         mCenter;
    QRect           mProjectionRect;
    QSize           mTargetWindowRect;
    QRectF          mCurrentWindowRect;
    float           mRotation;
    AspectRatioMode mAspectMode;
    FovMode         mFieldOfViewMode;
    bool            mAntialiasingEnabled;

    QMatrix         mMatrix;
    QList<Qtr2dCameraEffect*> mEffects;
};

#endif // PXSCAMERA_H
