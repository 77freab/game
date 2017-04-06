#include "tank.h"
#include "createMap.h"

extern std::map<osg::Vec2i, blockTypes> map;

tank::tank(int x, int z, std::string texTankType)
  : _dl(new tile(x, 0, z, texTankType + "UP_C1/dl.png")),
  _dr(new tile(x + 8, 0, z, texTankType + "UP_C1/dr.png")),
  _ul(new tile(x, 0, z + 8, texTankType + "UP_C1/ul.png")),
  _ur(new tile(x + 8, 0, z + 8, texTankType + "UP_C1/ur.png")),
  _texTankType(texTankType), _clb(new tankCallback),
  _x0(x), _z0(z), _x(x), _z(z)
{
  this->setDataVariance(osg::Object::DYNAMIC);
  this->setUpdateCallback(_clb);
  this->addChild(_dl);
  this->addChild(_dr);
  this->addChild(_ul);
  this->addChild(_ur);
}

void tank::shoot()
{
  _projectile = new projectile(_x + 4, 0, _z + 4, _curDir, "projectile/" + _texDir + ".png");
  this->getParent(0)->addChild(_projectile);
  _projectile->setName(this->getName() + " - projectile");
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
  osg::Vec2i collisionPt1, collisionPt2;
  if (_goDir == direction::UP)
  {
    collisionPt1 = { _x + 1, _z + 16 };
    collisionPt2 = { _x + 15, _z + 16 };
    _z++;
  }
  else if (_goDir == direction::DOWN)
  {
    collisionPt1 = { _x + 1, _z };
    collisionPt2 = { _x + 15, _z };
    _z--;
  }
  else if (_goDir == direction::LEFT)
  {
    collisionPt1 = { _x, _z + 1 };
    collisionPt2 = { _x, _z + 15 };
    _x--;
  }
  else if (_goDir == direction::RIGHT)
  {
    collisionPt1 = { _x + 16, _z + 1 };
    collisionPt2 = { _x + 16, _z + 15 };
    _x++;
  }

  //blockTypes a = map[{24, 16}];

  if (_curDir != _goDir)
  {
    switch (_goDir)
    {
    case(direction::UP) :
    {
      _texDir = "UP";
      break;
    }
    case(direction::DOWN) :
    {
      _texDir = "DOWN";
      break;
    }
    case(direction::LEFT) :
    {
      _texDir = "LEFT";
      break;
    }
    case(direction::RIGHT) :
    {
      _texDir = "RIGHT";
      break;
    }
    }
    _curDir = _goDir; // новое текущее направление
  }
  dynamic_cast<tile*>(this->getChild(0))->setTexture(_texTankType + _texDir + _texChassis + "dl.png");
  dynamic_cast<tile*>(this->getChild(1))->setTexture(_texTankType + _texDir + _texChassis + "dr.png");
  dynamic_cast<tile*>(this->getChild(2))->setTexture(_texTankType + _texDir + _texChassis + "ul.png");
  dynamic_cast<tile*>(this->getChild(3))->setTexture(_texTankType + _texDir + _texChassis + "ur.png");

  _texChassis == "_C1/" ? _texChassis = "_C2/" : _texChassis = "_C1/"; // меняем тип шасси

  mT.makeTranslate(_x - _x0, 0, _z - _z0);
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