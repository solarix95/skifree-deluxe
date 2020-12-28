#ifndef PXS_WIDGET_H
#define PXS_WIDGET_H

#include <QWidget>

class Qtr2dCamera;
class Qtr2dWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Qtr2dWidget(QWidget *parent = NULL);
    explicit Qtr2dWidget(Qtr2dCamera *camera, QWidget *parent = NULL);

    void setCamera(Qtr2dCamera *camera);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

signals:

public slots:

private:
    Qtr2dCamera *mCamera;
};

#endif // PXS_WIDGET_H
