#include <QDebug>
#include "qtr2dwidget.h"
#include "qtr2dcamera.h"
#include "qtr2dzone.h"

//-------------------------------------------------------------------------------------------------
Qtr2dWidget::Qtr2dWidget(QWidget *parent)
 : QWidget(parent)
 , mCamera(NULL)
{
}

//-------------------------------------------------------------------------------------------------
Qtr2dWidget::Qtr2dWidget(Qtr2dCamera *camera, QWidget *parent)
    : QWidget(parent)
    , mCamera(NULL)
{
    setCamera(camera);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    if (!mCamera) {
        p.fillRect(rect(), Qt::black);
        return;
    }

    mCamera->render(p);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::keyPressEvent(QKeyEvent *event)
{
    if (mCamera)
        mCamera->keyPressEvent(event);
    QWidget::keyPressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (mCamera)
        mCamera->keyReleaseEvent(event);
    QWidget::keyReleaseEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::setCamera(Qtr2dCamera *camera)
{
    mCamera = camera;
    if (!mCamera)
        return;

    connect(mCamera, SIGNAL(updateRequest()), this, SLOT(update()), Qt::UniqueConnection);
    mCamera->setProjectionRect(rect());
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::resizeEvent(QResizeEvent*)
{
    if (mCamera)
        mCamera->setProjectionRect(rect());
}
