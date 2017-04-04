#include "game.h"
#include <osgViewer/ViewerEventHandlers>
#include <osg/Texture2D>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <string>

viewerThread::viewerThread()
  : _viewer(new osgViewer::Viewer), _scene(createScene()),
  _keyHandler(new KeyboardEventHandler)
{
  _viewer->setUpViewInWindow(200, 400, 800, 700);
  _viewer->addEventHandler(_keyHandler);
  _viewer->setSceneData(_scene);
  //_viewer->addEventHandler(new osgViewer::StatsHandler());
  //_viewer->setRunMaxFrameRate(1); // ограничение кол-ва кадров в сек.
}

// вьювер запускается в отдельном потоке
void viewerThread::run()
{
  _viewer->run();
}

tile::tile(int x, int y, int z, std::string texPath)
  : _geode(new osg::Geode), _normals(new osg::Vec3Array), _geom(new osg::Geometry),
  _vertices(new osg::Vec3Array), _color(new osg::Vec4Array),
  _texCoord(new osg::Vec2Array), _image(osgDB::readImageFile("./Resources/" + texPath)),
  _texture(new osg::Texture2D)
{
  osg::Matrix m;
  m.makeTranslate(x, y, z);
  this->setMatrix(m);

  _geom->setColorArray(_color);
  _geom->setColorBinding(osg::Geometry::BIND_OVERALL);
  _color->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

  _geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
  
  _vertices->push_back(osg::Vec3(0, 0, 0));
  _vertices->push_back(osg::Vec3(8, 0, 0));
  _vertices->push_back(osg::Vec3(8, 0, 8));
  _vertices->push_back(osg::Vec3(0, 0, 8));
  _geom->setVertexArray(_vertices);

  _normals->setBinding(osg::Array::BIND_OVERALL);
  _normals->push_back(osg::Vec3(0, -1, 0));
  _geom->setNormalArray(_normals);

  _texCoord->push_back(osg::Vec2(0, 0));
  _texCoord->push_back(osg::Vec2(1, 0));
  _texCoord->push_back(osg::Vec2(1, 1));
  _texCoord->push_back(osg::Vec2(0, 1));
  _geom->setTexCoordArray(0, _texCoord);
  _texture->setImage(_image);
  _texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
  _texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::NEAREST);
  osg::StateSet* state = _geom->getOrCreateStateSet();
  state->setTextureAttributeAndModes(0, _texture);
  state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

  _geode->addDrawable(_geom);
  this->addChild(_geode);
}

osg::ref_ptr<osg::Group> viewerThread::createScene()
{
  osg::ref_ptr<osg::Group> scene = new osg::Group;
  void createMap(osg::ref_ptr<osg::Group> scene);
  createMap(scene);
  _tank.push_back = new tile(0, 0, -8, "yellow/t1_up_k1/dl.png"); // dl
  _tank.push_back = new tile(8, 0, -8, "yellow/t1_up_k1/dr.png"); // dr
  _tank.push_back = new tile(0, 0, 0, "yellow/t1_up_k1/ul.png"); // ul
  _tank.push_back = new tile(8, 0, 0, "yellow/t1_up_k1/ur.png"); // ur
  scene->addChild(_tank[0]);
  scene->addChild(_tank[1]);
  scene->addChild(_tank[2]);
  scene->addChild(_tank[3]);
  return scene;
}

bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
{
  switch (ea.getEventType())
  {
    case(osgGA::GUIEventAdapter::KEYDOWN) :
    {
      if (ea.getKey() == 119) // W
      {
        osg::Matrix m;
        m.makeTranslate(0, 0, 1);
        _tank[0]->setMatrix(m);
        _scene->addChild(new tile(16, 0, -8, "brick.png"));
        _scene->addChild(new tile(24, 0, -8, "brick.png"));
        _scene->addChild(new tile(16, 0, 0, "brick.png"));
        _scene->addChild(new tile(24, 0, 0, "brick.png"));
      }
      //_keyboardModel->keyChange(ea.getKey(), ea.getUnmodifiedKey(), 1);
      return true;
    }
    case(osgGA::GUIEventAdapter::KEYUP) :
    {
      //_keyboardModel->keyChange(ea.getKey(), ea.getUnmodifiedKey(), 0);
      return true;
    }
    default:
      return false;
  }
}