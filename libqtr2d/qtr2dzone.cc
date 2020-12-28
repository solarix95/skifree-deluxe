
#include <QTimer>
#include <QTime>
#include <QDebug>
#include "qtr2dbackground.h"
#include "qtr2dellipseparticle.h"
#include "qtr2dzone.h"
#include "qtr2dbody.h"
#include "qtr2dgravity.h"

#define GAME_INTERVAL (1000/60)

//-------------------------------------------------------------------------------------------------
Qtr2dZone::Qtr2dZone(QObject *parent)
    : QObject(parent)
    , mInputBody(NULL)
    , mBackground(NULL)
    , mGravity(NULL)
{
    qsrand(QTime::currentTime().minute() + QTime::currentTime().msec());
    mLastFps = 0;
    QTimer *t = new QTimer();
    connect(t, &QTimer::timeout, this, &Qtr2dZone::heartBeat);
    t->start(GAME_INTERVAL);
}

//-------------------------------------------------------------------------------------------------
Qtr2dZone::~Qtr2dZone()
{
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::render(QPainter &p, const QRectF &window)
{
    renderBackground(p, window);
    renderPlayers(p, window);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::clear()
{
    mInputBody = nullptr;
    qDeleteAll(mBodies);
    mBodies.clear();
    mParticles.clear();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::keyPressEvent(QKeyEvent *event)
{
    if (mInputBody)
        mInputBody->keyPressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::keyReleaseEvent(QKeyEvent *event)
{
    if (mInputBody)
        mInputBody->keyReleaseEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::createParticles(const QRectF &rect, const QVector2D &dir, int count, float radius, QColor c, int durationMs)
{
    QPointF pos;
    for (int i=0; i<count; i++) {
        QMatrix m;
        QPointF  p(dir.x(),dir.y());
        m.rotate(-15 + qrand()%30);
        m.scale(0.95 + (qrand()%10)/100.0f, 0.95 + (qrand()%10)/100.0f);

        p = p*m;
        pos.setX(rect.x() + ((qrand()%100)/100.0 * rect.width()));
        pos.setY(rect.y() + ((qrand()%100)/100.0 * rect.height()));
        registerObject(new Qtr2dEllipseParticle(pos,QVector2D(p.x(),p.y()),*this,c,durationMs,radius));
    }
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::createExplosion(const QPointF &pos, float force)
{
    Q_UNUSED(pos);
    Q_UNUSED(force);
    // Subclassing..!
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::appendBackground(Qtr2dBackground *bk)
{
    mBackground = bk;
    mBackground->setZone(this);
    emit updateRequest();
}

//-------------------------------------------------------------------------------------------------
bool Qtr2dZone::testCollision(Qtr2dObject *obj) const
{
    if (mBackground)
        return mBackground->testCollision(obj);
    return false;
}

//-------------------------------------------------------------------------------------------------
Qtr2dBody *Qtr2dZone::registerBody(Qtr2dBody *bdy, bool isInputBody)
{
    registerObject(bdy);
    if (isInputBody)
        mInputBody = bdy;
    return bdy;
}

//-------------------------------------------------------------------------------------------------
Qtr2dParticle *Qtr2dZone::registerParticle(Qtr2dParticle *ptcl)
{
    registerObject(ptcl);
    return ptcl;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::renderBackground(QPainter &p, const QRectF &window)
{
    if (mBackground)
        mBackground->render(p, window);
    else {
        p.setBrush(Qt::black);
        p.drawRect(window);
    }
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::renderPlayers(QPainter &p, const QRectF &window)
{
    foreach(Qtr2dBody *bdy, mBodies) {
        if (bdy->boundingRect().intersects(window))
            bdy->render(p);
    }

    foreach(const Qtr2dParticle *ptl, mParticles)
        if (window.contains(ptl->pos()))
            ptl->render(p);
}

//-------------------------------------------------------------------------------------------------
Qtr2dObject *Qtr2dZone::registerObject(Qtr2dObject *obj)
{
    Q_ASSERT(obj);

    Qtr2dBody *bdy = dynamic_cast<Qtr2dBody*>(obj);
    if (bdy) {
        connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(bodyDestroyed(QObject*)));
        mBodies << bdy;
    }
    Qtr2dParticle *ptcl = dynamic_cast<Qtr2dParticle*>(obj);
    if (ptcl) {
        connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(particleDestroyed(QObject*)));
        mParticles << ptcl;
    }
    connect(obj, SIGNAL(created(Qtr2dObject*)), this, SLOT(registerObject(Qtr2dObject*)));

    return obj;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::setGravity(Qtr2dGravity *g)
{
    if (mGravity) delete mGravity;
    mGravity = g;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::bodyDestroyed(QObject *bdy)
{
    mBodies.removeOne((Qtr2dBody*)bdy);
    if (mInputBody == (Qtr2dBody*)bdy)
        mInputBody = NULL;
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::particleDestroyed(QObject *ptl)
{
    mParticles.removeOne((Qtr2dParticle*)ptl);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::updateGravity()
{
    if (!mGravity)
        return;
    mGravity->process(mBodies,mParticles);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::heartBeat()
{
    if (mGameInterval.elapsed() <= 0) {
        mGameInterval.start();
        return;
    }
    mLastFps = 1000/mGameInterval.elapsed();
    process(mGameInterval.elapsed()/(float)GAME_INTERVAL);
    mGameInterval.start();
}

//-------------------------------------------------------------------------------------------------
void Qtr2dZone::process(double time)
{
    updateGravity();
    foreach(Qtr2dObject *obj, mBodies) {
        while (obj->move(time)) {
        }
    }

    foreach(Qtr2dObject *obj, mParticles) {
        while (obj->move(time)) {
        }
    }

    emit updateRequest();
}
