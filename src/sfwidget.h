#ifndef SFWIDGET_H
#define SFWIDGET_H

#include <qtr2dwidget.h>
#include <qtr2dfollowcamera.h>
#include <qtr2dsimplemenustyle.h>

#include "sfgame.h"

class SfWidget : public Qtr2dWidget
{
    Q_OBJECT
public:
    SfWidget(QWidget *parent = NULL);

private slots:
    void resetGame();

private:
    SfGame               mGame;
    Qtr2dFollowCamera    mCamera;
    Qtr2dSimpleMenuStyle mMenuStyle;
};

#endif // SFWIDGET_H
