#ifndef QTR2DOPTIONMENU_H
#define QTR2DOPTIONMENU_H

#include <QString>
#include <QList>
#include <QPixmap>
#include <QFont>
#include <qtr2dmenu.h>

//-------------------------------------------------------------------------------------------------
class Qtr2dMenuOption
{
public:
    Qtr2dMenuOption(const QPixmap &icon);
    Qtr2dMenuOption(const QPixmap &icon, const QString &text, const QFont &font);
    Qtr2dMenuOption(const QString &text, const QFont &font);

    QSize size() const;
    inline QPixmap icon() const { return mIcon; }
    inline QString text() const { return mText; }

private:
    QPixmap mIcon;
    QString mText;
    QFont   mFont;
};

typedef QList<Qtr2dMenuOption> Qtr2dMenuOptions;


//-------------------------------------------------------------------------------------------------
class Qtr2dOptionMenu : public Qtr2dMenu
{
    Q_OBJECT
public:
    Qtr2dOptionMenu(Qtr2dMenuStyle &style, const Qtr2dMenuOptions &options = Qtr2dMenuOptions());

    virtual QSize size() const;
    const Qtr2dMenuOption &option(int index) const;

signals:
    void selected(int index);

protected:
    virtual void renderContent(QPainter &p, const QSize &boxSize);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    QSize optionsMaxSize() const;

    Qtr2dMenuOptions mOptions;
    int              mCurrentIndex;
};

#endif // QTR2DOPTIONMENU_H
