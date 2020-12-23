#include <QApplication>
#include <qtr2dwidget.h>
#include <qtr2dfollowcamera.h>

#include "sfgame.h"

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);

  SfGame            game;
  Qtr2dFollowCamera cam(&game);
  Qtr2dWidget       widget;

  widget.setCamera(&cam);
  widget.setWindowTitle("Skifree Deluxe");

  QObject::connect(&game,SIGNAL(playerCreated(const Qtr2dObject*)), &cam, SLOT(followObject(const Qtr2dObject*)));
  game.init();
  cam.setFieldOfViewMode(Qtr2dCamera::NativeFov);
  cam.lookTo(0,0);

  widget.show();
  return app.exec();
}
