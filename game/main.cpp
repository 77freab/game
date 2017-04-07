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
  QObject::connect(myViewer, &viewerThread::closeGUI, &w, &game::close);
  QObject::connect(&w, &game::closeViewer, myViewer, &viewerThread::close);
  myViewer->start();
  return a.exec();
}
