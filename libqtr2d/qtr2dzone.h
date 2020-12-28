#ifndef PXS_ZONE_H
#define PXS_ZONE_H

#include <QObject>
#include <QList>
#include <QTime>
#include <QSizeF>
#include <QPainter>
#include <QKeyEvent>
#include "qtr2dbody.h"
#include "qtr2dparticle.h"

class Qtr2dCameraEffect;
class Qtr2dBackground;
class Qtr2dGravity;

class Qtr2dZone : public QObject
{
    Q_OBJECT
public:
    explicit Qtr2dZone(QObject *parent = nullptr);
    virtual ~Qtr2dZone();

    void render(QPainter &p, const QRectF &window);

    virtual void init() = 0; // create bodies, setup game, ...
    virtual void clear();

    inline const Qtr2dBodies    &bodies() const     { return mBodies;     }
    inline const PxsParticles &particles() const  { return mParticles;  }
    inline const QSize        &fieldSize() const  { return mFieldSize;  }
    inline QRect               fieldRect() const  { return QRect(0,0,mFieldSize.width(),mFieldSize.height()); }
    inline int                 fps() const        { return mLastFps;    }

    // User events
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    // Particle Factories
    virtual void createParticles(const QRectF &rect, const QVector2D &dir, int count, float radius, QColor c, int durationMs);
    virtual void createExplosion(const QPointF &pos, float force);

    virtual void appendBackground(Qtr2dBackground *bk);
    virtual bool testCollision(Qtr2dObject *obj) const;

signals:
    void updateRequest();
    void fieldSizeChanged();
    void requestCameraEffect(Qtr2dCameraEffect*);

protected slots:
        Qtr2dObject *registerObject(Qtr2dObject *obj);

protected:
    // Basic Setup
    void setFieldSize(const QSize &s) { mFieldSize = s; emit fieldSizeChanged(); emit updateRequest(); }
    void setGravity(Qtr2dGravity *g);

    // Creation of new Bodies
    virtual Qtr2dBody     *registerBody(Qtr2dBody *bdy, bool isInputBody = false);
    virtual Qtr2dParticle *registerParticle(Qtr2dParticle *ptcl);

    virtual void renderBackground(QPainter &p, const QRectF &window);
    virtual void renderPlayers(QPainter &p, const QRectF &window);

private slots:

    void bodyDestroyed(QObject *bdy);
    void particleDestroyed(QObject *bdy);
    void heartBeat();
    void process(double time);

private:
    void updateGravity();

    Qtr2dBodies      mBodies;
    Qtr2dBody       *mInputBody;
    PxsParticles     mParticles;
    Qtr2dBackground *mBackground;
    Qtr2dGravity    *mGravity;

    QSize          mFieldSize;
    QTime          mGameInterval;
    int            mLastFps;
};

#endif
