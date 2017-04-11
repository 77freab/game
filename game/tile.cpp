#include "tile.h"
#include <osgDB/ReadFile>

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

  /*_geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN, 0, 8));*/
  _geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

  _vertices->push_back(osg::Vec3(0, 0, 0)); // 1
  _vertices->push_back(osg::Vec3(8, 0, 0)); // 2
  _vertices->push_back(osg::Vec3(8, 0, 8)); // 3
  _vertices->push_back(osg::Vec3(0, 0, 8)); // 4

  //_vertices->push_back(osg::Vec3(0, 8, 0)); // 1
  //_vertices->push_back(osg::Vec3(8, 8, 0)); // 2
  //_vertices->push_back(osg::Vec3(8, 8, 8)); // 3
  //_vertices->push_back(osg::Vec3(0, 8, 8)); // 4

  //_vertices->push_back(osg::Vec3(0, 0, 8)); // 5
  //_vertices->push_back(osg::Vec3(0, 0, 0)); // 6
  //_vertices->push_back(osg::Vec3(8, 0, 0)); // 7
  //_vertices->push_back(osg::Vec3(8, 8, 0)); // 8
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