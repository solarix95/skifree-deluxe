#ifndef SFOBJECTS_H
#define SFOBJECTS_H

#include <QVariantMap>
#include <QMap>
#include <QString>
#include <QPixmap>
#include <QStringList>

#include <qtr2dbody.h>
#include <qtr2dzone.h>

class SfObjects
{
public:
    SfObjects();

    void init(Qtr2dZone &zone, const QVariantMap &jsonConfig);
    Qtr2dBody *create(const QString &name, const QPointF &pos);
    QStringList playerList() const;
    QPixmap     icon(const QString &name) const;

private:
    Qtr2dBody *createStaticBody(const QVariantMap &jsonConfig, const QPointF &pos);
    Qtr2dBody *createPlayerBody(const QVariantMap &jsonConfig, const QPointF &pos);


    bool           config2Sprite(const QVariantMap &jsonConfig, QPixmap &sprite);
    bool           spriteInfo(const QVariantMap &jsonConfig, QString &name, QRect &rect) const;
    const QPixmap &spriteByName(const QString &name);
    void           applyAttributes(Qtr2dObject *obj, const QVariantMap &jsonConfig) const;

    Qtr2dZone            *mZone;
    QMap<QString,QPixmap> mSprites;
    QVariantMap           mObjectsConfig;
};

#endif // SFOBJECTS_H
