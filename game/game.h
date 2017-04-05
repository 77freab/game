#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QThread>
#include <osg/ref_ptr>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <functional>

enum direction
{
  UP = 0,
  LEFT = 1,
  DOWN = 2,
  RIGHT = 3
};

class ndCallback : public osg::NodeCallback
{
public:
  void operator()(osg::Node*, osg::NodeVisitor*);
};

class tile : public osg::MatrixTransform
{
public:
  tile(int x, int y, int z, std::string texPath);
  void setTexture(std::string texPath);
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

class projectile : public tile
{
public:
  projectile(int x, int y, int z, enum direction, std::string texPath);
  std::function<void()> move;
  direction _dir;
  osg::Matrix mT;
  int _x;
  int _z;
};

class tank : public osg::MatrixTransform
{
public:
  tank(int x, int z, std::string texPath);
  void moveTo(enum direction dir);
  void shoot();
private:
  osg::ref_ptr<tile> _dl;
  osg::ref_ptr<tile> _dr;
  osg::ref_ptr<tile> _ul;
  osg::ref_ptr<tile> _ur;
  osg::ref_ptr<projectile> _projectile = nullptr;
  int _x;
  int _z;
  direction _curDir = UP;
  std::string _texDir = "UP";
  std::string _texTankType;
  std::string _texChassis = "_C1/";
  osg::ref_ptr<ndCallback> _clb;
};

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
