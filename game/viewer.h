#pragma once

#include "tank.h"
#include <QThread>
#include <osgViewer/Viewer>


class viewerThread : public QThread, public osgGA::GUIEventHandler
{
public:
  viewerThread();
  osg::ref_ptr<osg::Group> createScene();
  osg::ref_ptr<osgViewer::Viewer> _viewer;
  void run() override;
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
private:
  osg::ref_ptr<osg::Group> _scene;
  osg::ref_ptr<tank> _tank;
  std::map<int, bool> _pressedKeysFirstPlayer;
  //std::map<std::string, bool> _pressedKeysSecondPlayer = { // переделать под коды клавиш
  //  { "UpArow", false }, // UpArow
  //  { "DownArrow", false }, // DownArrow
  //  { "LeftArrow", false }, // LeftArrow
  //  { "RightArrow", false } }; // RightArrow
};