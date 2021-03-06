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

    Qtr2dBody *body = NULL;
    if (bodyType == "static")
        body = createStaticBody(bodyConfig, pos);

    if (bodyType == "player")
        body = createPlayerBody(bodyConfig, pos);

    applyAttributes(body,bodyConfig);
    return body;
}

//-------------------------------------------------------------------------------------------------
QStringList SfObjects::playerList() const
{
    QStringList keys = mObjectsConfig.keys();
    QStringList players;

    foreach(QString key, keys) {
        if (mObjectsConfig[key].toMap()["type"] == "player")
            players << key;
    }

    return players;
}

//-------------------------------------------------------------------------------------------------
QPixmap SfObjects::icon(const QString &name) const
{
    QVariantMap iconConfig = mObjectsConfig[name].toMap()["icon"].toMap();

    QString fileName;
    QRect   iconRect;
    if (!spriteInfo(iconConfig,fileName,iconRect))
        return QPixmap();

    // Create icon -> but const (config2Sprite() is non const...)
    QPixmap parentImage;
    if (mSprites.contains(fileName))
        parentImage = mSprites[fileName];
    else
        parentImage = QPixmap(fileName);

    return parentImage.copy(iconRect);
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

    SfPlayer *p = new SfPlayer(pos,*mZone);

    QPixmap leftSprite;
    QPixmap rightSprite;
    QPixmap crashedSprite;

    config2Sprite(spritesConfig["left"].toMap(),leftSprite);
    config2Sprite(spritesConfig["right"].toMap(),rightSprite);
    config2Sprite(spritesConfig["crashed"].toMap(),crashedSprite);

    if (leftSprite.isNull() && !rightSprite.isNull())
        leftSprite = QPixmap::fromImage(rightSprite.toImage().mirrored(true,false));

    if (rightSprite.isNull() && !leftSprite.isNull())
        rightSprite = QPixmap::fromImage(leftSprite.toImage().mirrored(true,false));

    p->appendSprite(SfPlayer::LeftState,leftSprite);
    p->appendSprite(SfPlayer::RightState,rightSprite);
    p->appendSprite(SfPlayer::CrashedState,crashedSprite);

    bool done = false;
    float speed = jsonConfig["speed"].toFloat(&done);
    if (done)
        p->setSpeed(speed);

    return p;
}

//-------------------------------------------------------------------------------------------------
bool SfObjects::config2Sprite(const QVariantMap &jsonConfig, QPixmap &sprite)
{
    QString     spriteName;
    QRect       rect;
    if (!spriteInfo(jsonConfig,spriteName,rect))
        return false;

    sprite = spriteByName(spriteName).copy(rect);
    return true;
}

//-------------------------------------------------------------------------------------------------
bool SfObjects::spriteInfo(const QVariantMap &jsonConfig, QString &name, QRect &rect) const
{
    name  = jsonConfig["sprite"].toString();
    QStringList rectParts   = jsonConfig["rect"].toString().split(" ");
    if (name.isEmpty())
        return false;

    if (rectParts.count() != 4)
        return false;

    rect   = QRect(rectParts[0].toInt(),rectParts[1].toInt(),rectParts[2].toInt(),rectParts[3].toInt());
    if (!rect.isValid())
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------
const QPixmap &SfObjects::spriteByName(const QString &name)
{
    if (!mSprites.contains(name))
        mSprites[name] = QPixmap(name);

    return mSprites[name];
}

//-------------------------------------------------------------------------------------------------
void SfObjects::applyAttributes(Qtr2dObject *obj, const QVariantMap &jsonConfig) const
{
    if (!obj)
        return;
    QVariantMap attributes = jsonConfig["attributes"].toMap();
    if (attributes.isEmpty())
        return;
    for (auto key: attributes.keys())
        obj->setAttribute(key, attributes[key]);
}

