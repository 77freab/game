#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QThread>
#include <osg/ref_ptr>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
//#include <vector>

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
};

class tile : public osg::MatrixTransform
{
public:
  tile(int x, int y, int z, std::string texPath);
private:
  osg::ref_ptr<osg::Geode> _geode;
  osg::ref_ptr<osg::Geometry> _geom;
  osg::ref_ptr<osg::Vec4Array> _color;
  osg::ref_ptr<osg::Vec3Array> _vertices;
  osg::ref_ptr<osg::Vec3Array> _normals;
  osg::ref_ptr<osg::Vec2Array> _texCoord;
  osg::ref_ptr<osg::Image> _image;
  osg::ref_ptr<osg::Texture2D> _texture;
};

class viewerThread : public QThread, public osg::Referenced
{
public:
  viewerThread();
  osg::ref_ptr<osg::Group> createScene();
  osg::ref_ptr<osgViewer::Viewer> _viewer;
  void run() override;
private:
  osg::ref_ptr<osg::Group> _scene;
  std::vector<osg::ref_ptr<tile>> _tank;
  KeyboardEventHandler* _keyHandler;
};

class game : public QWidget
{
  Q_OBJECT
public:
  game(QWidget *parent = Q_NULLPTR);
private:
  QPushButton* _btn;
  QVBoxLayout* _vLayout;
};
