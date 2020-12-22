
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QVariantMap>
#include <QJsonDocument>
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
    QFile f(":/skifree.json");
    bool done = f.open(QIODevice::ReadOnly);
    Q_ASSERT(done);
    QVariantMap config = QJsonDocument::fromJson(f.readAll()).toVariant().toMap();

    mSprites.init(config);
    mObjects.init(*this, config);

    setFieldSize(QSize(10,10));
    appendBackground(new Qtr2dBrushBackground(Qt::white));


    registerBody(new SfTree(mSprites,QPointF(10,10),*this));
    registerBody(mObjects.create("tree1"));
}

