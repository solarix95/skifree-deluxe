#ifndef QTR2DMENU_H
#define QTR2DMENU_H

#include <QPainter>
#include <QObject>
#include <QKeyEvent>
#include <qtr2dmenustyle.h>

class Qtr2dMenu : public QObject
{
    Q_OBJECT
public:
    Qtr2dMenu(Qtr2dMenuStyle &style, QObject *parent = NULL);

    virtual void keyEvent(QKeyEvent *event);
    void render(QPainter &p, const QRect &window);

    virtual QSize size() const = 0;

signals:
    void updateRequest();

protected:
    virtual void renderBox(QPainter &p, const QSize &boxSize);
    virtual void renderContent(QPainter &p, const QSize &boxSize) = 0;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    const Qtr2dMenuStyle &style() const;

private:
    Qtr2dMenuStyle &mStyle;

};

#endif // QTR2DMENU_H
