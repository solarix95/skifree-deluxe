
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
 : mSceneryY(0)
{
}

//-------------------------------------------------------------------------------------------------
QStringList SfGame::playerList() const
{
    return mObjects.playerList();
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


    initGame();
}

//-------------------------------------------------------------------------------------------------
void SfGame::reset(const QString &playerName)
{
    clear();
    initGame(playerName);
}

//-------------------------------------------------------------------------------------------------
void SfGame::initGame(const QString &playerName)
{
    mSceneryY = 10;

    registerBody(mObjects.create("chris-pirih",QPointF(-200,200)));

    // Start is centered in the screen, camera looks to 0/0:
    registerBody(mObjects.create("start-left",QPointF(-70,0)));
    registerBody(mObjects.create("start-right",QPointF(70,0)));

    registerBody(mObjects.create("help-flag",QPointF(200,100)));

    QStringList players = mObjects.playerList();
    if (playerName.isEmpty())
        mPlayer = registerBody(mObjects.create(players[qrand()%players.count()],QPointF(0,200)),true);
    else
        mPlayer = registerBody(mObjects.create(playerName,QPointF(0,200)),true);

    connect(mPlayer, &Qtr2dBody::changed, this, &SfGame::updateScenery);

    emit playerCreated(mPlayer);

    updateScenery();
}

//-------------------------------------------------------------------------------------------------
void SfGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F2) {
        reset();
    }
    Qtr2dZone::keyPressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void SfGame::updateScenery()
{
    if ((mPlayer->pos().y() - 500) > mSceneryY)
        return;

    int minX = mPlayer->pos().x() - 2000;
    int maxX = mPlayer->pos().x() + 2000;

    int minY = mSceneryY;
    int maxY = mSceneryY - 500;


    QStringList staticObjs = { "tree1", "tree2", "tree3", "tree4", "tree5","tree6","stone1","stone1","stone3" };

    for (int i=0; i<50; i++) {
        int x = minX + (qrand() % (maxX - minX));
        int y = minY - (qrand() % (maxY - minY));
        registerBody(mObjects.create(staticObjs[qrand()%staticObjs.count()],QPointF(x,y)));
    }

    mSceneryY = maxY;

    // Remove top/old objects
    int deleted = 0;
    const Qtr2dBodies &bdys = bodies();
    int topY = mPlayer->pos().y() + 500;
    for (int i=0; i<bdys.count(); i++) {
        if (bdys[i]->pos().y() > topY) {
            bdys[i]->deleteLater();
            deleted++;
        }
        if (deleted > 50)
            return;
    }
}

