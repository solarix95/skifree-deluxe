#ifndef SFWIDGET_H
#define SFWIDGET_H

#include <qtr2dwidget.h>
#include <qtr2dfollowcamera.h>
#include <qtr2dwin311menustyle.h>

#include "sfgame.h"

class SfWidget : public Qtr2dWidget
{
    Q_OBJECT
public:
    SfWidget(QWidget *parent = NULL);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void resetGame();

private:
    SfGame               mGame;
    Qtr2dFollowCamera    mCamera;
    Qtr2dWin311MenuStyle mMenuStyle;
};

#endif // SFWIDGET_H
