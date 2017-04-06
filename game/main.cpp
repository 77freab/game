#include "GUI.h"
#include "viewer.h"
#include <osg/ref_ptr>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  game w;
  w.show();
  osg::ref_ptr<viewerThread> myViewer = new viewerThread;
  myViewer->start();
  return a.exec();
}
