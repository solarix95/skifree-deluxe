#ifndef SFGAME_H
#define SFGAME_H

#include <QObject>
#include <qtr2dzone.h>
#include <qtr2dbody.h>
#include "sfsprites.h"
#include "sfobjects.h"


class SfGame : public Qtr2dZone
{
    Q_OBJECT
public:
    SfGame();

    virtual void init();

public slots:
    void initGame();

signals:
    void playerCreated(const Qtr2dObject *player);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void updateScenery();

private:
    Qtr2dBody    *mPlayer;
    int           mSceneryY;
    SfObjects     mObjects;
    SfSprites     mSprites;
};

#endif // SFGAME_H
