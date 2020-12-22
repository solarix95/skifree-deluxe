#ifndef SFSPRITES_H
#define SFSPRITES_H

#include <QPixmap>
#include <QVariantMap>
#include <QMap>

class SfSprites
{
public:
    SfSprites();

    void init(const QVariantMap &jsonConfig);
    const QPixmap &sprite(int key) const;

private:

    QMap<int,QPixmap> mSprites;
};

#endif // SFSPRITES_H
