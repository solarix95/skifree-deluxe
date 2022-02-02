#include <QApplication>

#include "sfwidget.h"

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);

  SfWidget w;
  w.show();

  return app.exec();
}
