#ifndef SFAUTOPLAYER_H
#define SFAUTOPLAYER_H

#include "sfplayer.h"

class SfAutoPlayer : public SfPlayer
{
public:
    SfAutoPlayer(const QPointF &p, Qtr2dZone &zone);
};

#endif // SFAUTOPLAYER_H
