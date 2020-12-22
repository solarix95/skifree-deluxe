#ifndef SFOBJECTS_H
#define SFOBJECTS_H

#include <QVariantMap>
#include <QMap>
#include <QString>
#include <QPixmap>

#include <qtr2dbody.h>
#include <qtr2dzone.h>

class SfObjects
{
public:
    SfObjects();

    void init(Qtr2dZone &zone, const QVariantMap &jsonConfig);
    Qtr2dBody *create(const QString &name);

private:
    Qtr2dBody *createStaticBody(const QVariantMap &jsonConfig);
    const QPixmap &spriteByName(const QString &name);

    Qtr2dZone            *mZone;
    QMap<QString,QPixmap> mSprites;
    QVariantMap           mObjectsConfig;
};

#endif // SFOBJECTS_H
