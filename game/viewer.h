#pragma once

#include "tank.h"
#include <QThread>
#include <osgViewer/Viewer>


class viewerThread : public QThread, public osgGA::GUIEventHandler
{
  Q_OBJECT
public:
  viewerThread();
  osg::ref_ptr<osg::Group> createScene();
  osg::ref_ptr<osgViewer::Viewer> _viewer;
  void run() override;
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
signals:
  void closeGUI();
public slots:
void close();
private:
  osg::ref_ptr<osg::Group> _scene;
  osg::ref_ptr<tank> _p1Tank;
  osg::ref_ptr<tank> _p2Tank;
  std::map<int, bool> _pressedKeysP1;
  std::map<int, bool> _pressedKeysP2;
  //std::map<std::string, bool> _pressedKeysSecondPlayer = { // переделать под коды клавиш
  //  { "UpArow", false }, // UpArow
  //  { "DownArrow", false }, // DownArrow
  //  { "LeftArrow", false }, // LeftArrow
  //  { "RightArrow", false } }; // RightArrow
};