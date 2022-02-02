#ifndef PXS_WIDGET_H
#define PXS_WIDGET_H

#include <QWidget>

class Qtr2dCamera;
class Qtr2dMenu;

class Qtr2dWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Qtr2dWidget(QWidget *parent = NULL);
    explicit Qtr2dWidget(Qtr2dCamera *camera, QWidget *parent = NULL);

    void setCamera(Qtr2dCamera *camera);
    void setMenu(Qtr2dMenu *menu);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void onStateChange();

signals:
    void stateChanged();

public slots:

private slots:
    void menuDestroyed(QObject *menu);

private:
    Qtr2dCamera *mCamera;
    Qtr2dMenu   *mMenu;
};

#endif // PXS_WIDGET_H
