#include <QApplication>
#include <qtr2dwidget.h>
#include <qtr2dcamera.h>

#include "sfgame.h"

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);

  SfGame game;
  Qtr2dCamera cam(&game);
  Qtr2dWidget widget;
  widget.setCamera(&cam);
  widget.setWindowTitle("Skifree Deluxe");
  game.init();
  cam.lookTo(50,50);

  widget.show();
  return app.exec();
}
