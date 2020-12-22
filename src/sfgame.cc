
#include <QTimer>
#include <QDebug>

#include <qtr2dbrushbackground.h>

#include "sfgame.h"
#include "sftree.h"

//-------------------------------------------------------------------------------------------------
SfGame::SfGame()
{

}

//-------------------------------------------------------------------------------------------------
void SfGame::init()
{
    setFieldSize(QSize(100,100));
    appendBackground(new Qtr2dBrushBackground(Qt::white));


    registerBody(new SfTree(mSprites,QPointF(10,10),*this));
}

