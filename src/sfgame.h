#ifndef SFGAME_H
#define SFGAME_H

#include <QObject>
#include <qtr2dzone.h>
#include "sfsprites.h"


class SfGame : public Qtr2dZone
{
    Q_OBJECT
public:
    SfGame();

    virtual void init();

private slots:


signals:

private:
    SfSprites mSprites;
};

#endif // SFGAME_H
