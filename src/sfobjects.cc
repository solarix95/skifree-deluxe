#include <QStringList>
#include "sfobjects.h"
#include "sfstaticobject.h"

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
Qtr2dBody *SfObjects::create(const QString &name)
{
    QVariantMap bodyConfig = mObjectsConfig[name].toMap();
    Q_ASSERT(!bodyConfig.isEmpty());

    QString bodyType = bodyConfig["type"].toString();
    if (bodyType == "static")
        return createStaticBody(bodyConfig);
    return NULL;
}

//-------------------------------------------------------------------------------------------------
Qtr2dBody *SfObjects::createStaticBody(const QVariantMap &jsonConfig)
{
    QString     spriteName  = jsonConfig["sprite"].toString();
    QStringList rectParts   = jsonConfig["rect"].toString().split(" ");

    Q_ASSERT(!spriteName.isEmpty());
    Q_ASSERT( rectParts.count() == 4);


    QPixmap sprite = spriteByName(spriteName);
    QRect   rect   = QRect(rectParts[0].toInt(),rectParts[1].toInt(),rectParts[2].toInt(),rectParts[3].toInt());
    sprite = sprite.copy(rect);

    return new SfStaticObject(sprite,QRect(),QPointF(),*mZone);
}

//-------------------------------------------------------------------------------------------------
const QPixmap &SfObjects::spriteByName(const QString &name)
{
    if (!mSprites.contains(name))
        mSprites[name] = QPixmap(name);

    return mSprites[name];
}

