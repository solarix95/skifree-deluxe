#include <QStringList>
#include "sfobjects.h"
#include "sfstaticobject.h"
#include "sfplayer.h"

//-------------------------------------------------------------------------------------------------
SfObjects::SfObjects()
 : mZone(NULL)
{
}

//-------------------------------------------------------------------------------------------------
void SfObjects::init(Qtr2dZone &zone, const QVariantMap &jsonConfig)
{
    mZone = &zone;
    mObjectsConfig = jsonConfig["objects"].toMap();
}

//-------------------------------------------------------------------------------------------------
Qtr2dBody *SfObjects::create(const QString &name, const QPointF &pos)
{
    QVariantMap bodyConfig = mObjectsConfig[name].toMap();
    Q_ASSERT(!bodyConfig.isEmpty());

    QString bodyType = bodyConfig["type"].toString();
    if (bodyType == "static")
        return createStaticBody(bodyConfig, pos);

    if (bodyType == "player")
        return createPlayerBody(bodyConfig, pos);

    return NULL;
}

//-------------------------------------------------------------------------------------------------
Qtr2dBody *SfObjects::createStaticBody(const QVariantMap &jsonConfig, const QPointF &pos)
{
    QPixmap sprite;
    config2Sprite(jsonConfig,sprite);

    return new SfStaticObject(sprite,QRect(),pos,*mZone);
}

//-------------------------------------------------------------------------------------------------
Qtr2dBody *SfObjects::createPlayerBody(const QVariantMap &jsonConfig, const QPointF &pos)
{
    QVariantMap spritesConfig = jsonConfig["sprites"].toMap();
    QPixmap sprite;

    SfPlayer *p = new SfPlayer(pos,*mZone);
    if (config2Sprite(spritesConfig["left"].toMap(),sprite))
        p->appendSprite(SfPlayer::LeftState,sprite);

    if (config2Sprite(spritesConfig["right"].toMap(),sprite))
        p->appendSprite(SfPlayer::RightState,sprite);

    if (config2Sprite(spritesConfig["crashed"].toMap(),sprite))
        p->appendSprite(SfPlayer::CrashedState,sprite);

    return p;
}

//-------------------------------------------------------------------------------------------------
bool SfObjects::config2Sprite(const QVariantMap &jsonConfig, QPixmap &sprite)
{
    if (jsonConfig.isEmpty())
        return false;

    QString     spriteName  = jsonConfig["sprite"].toString();
    QStringList rectParts   = jsonConfig["rect"].toString().split(" ");
    Q_ASSERT(!spriteName.isEmpty());
    Q_ASSERT( rectParts.count() == 4);


    sprite = spriteByName(spriteName);
    QRect   rect   = QRect(rectParts[0].toInt(),rectParts[1].toInt(),rectParts[2].toInt(),rectParts[3].toInt());
    sprite = sprite.copy(rect);

    return true;
}

//-------------------------------------------------------------------------------------------------
const QPixmap &SfObjects::spriteByName(const QString &name)
{
    if (!mSprites.contains(name))
        mSprites[name] = QPixmap(name);

    return mSprites[name];
}

