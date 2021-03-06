#include <QDebug>
#include "qtr2dwidget.h"
#include "qtr2dcamera.h"
#include "qtr2dmenu.h"
#include "qtr2dzone.h"

//-------------------------------------------------------------------------------------------------
Qtr2dWidget::Qtr2dWidget(QWidget *parent)
 : QWidget(parent)
 , mCamera(NULL)
 , mMenu(NULL)
{
}

//-------------------------------------------------------------------------------------------------
Qtr2dWidget::Qtr2dWidget(Qtr2dCamera *camera, QWidget *parent)
    : QWidget(parent)
    , mCamera(NULL)
    , mMenu(NULL)
{
    setCamera(camera);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    if (mCamera)
         mCamera->render(p);
    else
        p.fillRect(rect(), Qt::black);

    if (mMenu) {
        QRect menuRect(0,0,mMenu->size().width(), mMenu->size().height());
        menuRect.translate(rect().center()-menuRect.center());

        p.save();
        mMenu->render(p,menuRect);
        p.restore();
    }
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::keyPressEvent(QKeyEvent *event)
{
    if (mMenu)
        mMenu->keyEvent(event);

    if (mCamera)
        mCamera->keyPressEvent(event);

    QWidget::keyPressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (mMenu)
        mMenu->keyEvent(event);

    if (mCamera)
        mCamera->keyReleaseEvent(event);

    QWidget::keyReleaseEvent(event);
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::menuDestroyed(QObject *menu)
{
    if (menu == (QObject*)mMenu)
        mMenu = nullptr;
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
void Qtr2dWidget::setMenu(Qtr2dMenu *menu)
{
    mMenu = menu;
    connect(mMenu, SIGNAL(updateRequest()), this, SLOT(update()));
    connect(mMenu, SIGNAL(destroyed(QObject*)), this, SLOT(menuDestroyed(QObject*)));
}

//-------------------------------------------------------------------------------------------------
void Qtr2dWidget::resizeEvent(QResizeEvent*)
{
    if (mCamera)
        mCamera->setProjectionRect(rect());
}
