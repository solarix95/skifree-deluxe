#ifndef PXSCAMERAEFFECT_H
#define PXSCAMERAEFFECT_H

#include <QObject>
#include <QTime>
#include <QMatrix>

class Qtr2dCameraEffect : public QObject
{
    Q_OBJECT
public:
    Qtr2dCameraEffect(int fps = 30);

    virtual void process(QMatrix &matrix, const QRectF &window) = 0;

signals:
    void updateRequest();

protected slots:
    virtual void update();

protected:
    int  elapsedMs() const;

private:
    QTime  mTime;
};

#endif // PXSCAMERAEFFECT_H
