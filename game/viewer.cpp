#include "game.h"
#include <osgViewer/ViewerEventHandlers>
#include <osg/Texture2D>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <string>

viewerThread::viewerThread()
  : _viewer(new osgViewer::Viewer)
{
  _scene = createScene();
  _viewer->setUpViewInWindow(200, 400, 800, 700);
  _viewer->addEventHandler(this);
  _viewer->setSceneData(_scene);
  //_viewer->addEventHandler(new osgViewer::StatsHandler());
  //_viewer->setRunMaxFrameRate(1); // ����������� ���-�� ������ � ���.
}

// ������ ����������� � ��������� ������
void viewerThread::run()
{
  _viewer->run();
}

void tile::setTexture(std::string texPath)
{
  _image = osgDB::readImageFile("./Resources/" + texPath);
  _texture->setImage(_image);
  _texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
  _texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::NEAREST);
  osg::StateSet* state = _geom->getOrCreateStateSet();
  state->setTextureAttributeAndModes(0, _texture);
  state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
}

tile::tile(int x, int y, int z, std::string texPath)
  : _geode(new osg::Geode), _normals(new osg::Vec3Array), _geom(new osg::Geometry),
  _vertices(new osg::Vec3Array), _color(new osg::Vec4Array),
  _texCoord(new osg::Vec2Array), _texture(new osg::Texture2D)
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
  setTexture(texPath);

  _geode->addDrawable(_geom);
  this->addChild(_geode);
}

tank::tank(int x, int z, std::string texTankType)
  : _dl(new tile(  x, 0, z-8, texTankType + "UP_C1/dl.png")),
    _dr(new tile(x+8, 0, z-8, texTankType + "UP_C1/dr.png")),
    _ul(new tile(  x, 0,   z, texTankType + "UP_C1/ul.png")),
    _ur(new tile(x+8, 0,   z, texTankType + "UP_C1/ur.png")),
    _x(x), _z(z), _texTankType(texTankType),
    _clb(new tankCallback)
{
  this->setDataVariance(osg::Object::DYNAMIC);
  this->setUpdateCallback(_clb);
  this->addChild(_dl);
  this->addChild(_dr);
  this->addChild(_ul);
  this->addChild(_ur);
}

void tank::moveTo(direction dir)
{
  _go = true;
  _goDir = dir;
}

void tank::stop()
{
  _go = false;
}

void tank::move()
{
  osg::Matrix mT;
  if (_goDir == UP)
    _z++;
  else if (_goDir == DOWN)
    _z--;
  else if (_goDir == LEFT)
    _x--;
  else if (_goDir == RIGHT)
    _x++;
  if (_curDir != _goDir)
  {
    switch (_goDir)
    {
      case(UP) :
      {
        _texDir = "UP";
        break;
      }
      case(DOWN) :
      {
        _texDir = "DOWN";
        break;
      }
      case(LEFT) :
      {
        _texDir = "LEFT";
        break;
      }
      case(RIGHT) :
      {
        _texDir = "RIGHT";
        break;
      }
    }
    _curDir = _goDir; // ����� ������� �����������
  }
  dynamic_cast<tile*>(this->getChild(0))->setTexture(_texTankType + _texDir + _texChassis + "dl.png");
  dynamic_cast<tile*>(this->getChild(1))->setTexture(_texTankType + _texDir + _texChassis + "dr.png");
  dynamic_cast<tile*>(this->getChild(2))->setTexture(_texTankType + _texDir + _texChassis + "ul.png");
  dynamic_cast<tile*>(this->getChild(3))->setTexture(_texTankType + _texDir + _texChassis + "ur.png");
  _texChassis == "_C1/" ? _texChassis = "_C2/" : _texChassis = "_C1/"; // ������ ��� �����

  mT.makeTranslate(_x, 0, _z);
  this->setMatrix(mT);
}

projectile::projectile(int x, int y, int z, direction dir, std::string texPath)
  : tile(x, y, z, texPath), _dir(dir), _x(x), _z(z), _clb(new projectileCallback)
{
  this->setDataVariance(osg::Object::DYNAMIC);
  this->setUpdateCallback(_clb);
  switch (_dir)
  {
    case(direction::UP) :
    {
      move = [this] 
      { 
        _z += 4; 
        mT.makeTranslate(_x, 0, _z);
        this->setMatrix(mT); 
      };
      break;
    }
    case(direction::DOWN) :
    {
      move = [this] 
      { 
        _z -= 4;
        mT.makeTranslate(_x, 0, _z);
        this->setMatrix(mT);
      };
      break;
    }
    case(direction::LEFT) :
    {
      move = [this] 
      { 
        _x -= 4;
        mT.makeTranslate(_x, 0, _z);
        this->setMatrix(mT);
      };
      break;
    }
    case(direction::RIGHT) :
    {
      move = [this] 
      { 
        _x += 4;
        mT.makeTranslate(_x, 0, _z);
        this->setMatrix(mT);
      };
      break;
    }
  }
}

void tank::shoot()
{
  _projectile = new projectile(_x+4, 0, _z-4, _curDir, "projectile/" + _texDir + ".png");
  this->getParent(0)->addChild(_projectile);
  _projectile->setName(this->getName() + " - projectile");
}

void projectileCallback::operator()(osg::Node* nd, osg::NodeVisitor* ndv)
{
  projectile* prj = dynamic_cast<projectile*>(nd);
  prj->move();
  traverse(nd, ndv);
}

void tankCallback::operator()(osg::Node* nd, osg::NodeVisitor* ndv)
{
  tank* tnk = dynamic_cast<tank*>(nd);
  if (tnk->_go)
    tnk->move();
  traverse(nd, ndv);
}

osg::ref_ptr<osg::Group> viewerThread::createScene()
{
  osg::ref_ptr<osg::Group> scene = new osg::Group;
  scene->setName("main scene");
  void createMap(osg::ref_ptr<osg::Group> scene);
  createMap(scene);
  _tank = new tank(0, 0, "yellow/T1_");
  scene->addChild(_tank);
  _tank->setName(scene->getName() + " - main tank");
  return scene;
}

bool viewerThread::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
{
  switch (ea.getEventType())
  {
    case(osgGA::GUIEventAdapter::KEYDOWN) :
    {
      switch (ea.getKey())
      {
        case(119): // W
        {
          _pressedKeysFirstPlayer[119] = true;
          _tank->moveTo(direction::UP);
          break;
        }
        case(115) : // S
        {
          _pressedKeysFirstPlayer[115] = true;
          _tank->moveTo(direction::DOWN);
          break;
        }
        case(97) : // A
        {
          _pressedKeysFirstPlayer[97] = true;
          _tank->moveTo(direction::LEFT);
          break;
        }
        case(100) : // D
        {
          _pressedKeysFirstPlayer[100] = true;
          _tank->moveTo(direction::RIGHT);
          break;
        }
        case(32) : // SPACE
        {
          _tank->shoot();
          break;
        }
      }
      return true;
    }
    case(osgGA::GUIEventAdapter::KEYUP) :
    {
      int key = ea.getKey();
      switch (key)
      {
        case(119) : // W
        case(115) : // S
        case(97) : // A
        case(100) : // D
        {
          _pressedKeysFirstPlayer[key] = false;
          // ���� ��� ���� ������������ ������� ������� �� ���� ���������������
          if (!(_pressedKeysFirstPlayer[119] | _pressedKeysFirstPlayer[115] |
            _pressedKeysFirstPlayer[97] | _pressedKeysFirstPlayer[100]))
            _tank->stop();
          break;
        }
      }
      return true;
    }
    default:
      return false;
  }
}