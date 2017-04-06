#include "tile.h"
#include <createMap.h>

const int MAP_X_SIZE = 32;
const int MAP_Z_SIZE = 28;

void createMap(osg::ref_ptr<osg::Group> scene)
{
  std::map<blockTypes, std::string> blockTex = {
    { blockTypes::BORDER, "blocks/BORDER.png" },
    { blockTypes::BRICK, "blocks/BRICK.png" },
    { blockTypes::ARMOR, "blocks/ARMOR.png" },
    { blockTypes::WATER, "blocks/WATER.png" },
    { blockTypes::BUSHES, "blocks/BUSHES.png" },
    { blockTypes::ICE, "blocks/ICE.png" } };

  std::map<osg::Vec2i, blockTypes> map;

  for (int z = 24; z < 200; z += 8)
  {
    if (z == 80)
      z = 128;
    map[{32, z}] = blockTypes::BRICK;
    map[{40, z}] = blockTypes::BRICK;

    map[{64, z}] = blockTypes::BRICK;
    map[{72, z}] = blockTypes::BRICK;

    map[{160, z}] = blockTypes::BRICK;
    map[{168, z}] = blockTypes::BRICK;

    map[{192, z}] = blockTypes::BRICK;
    map[{200, z}] = blockTypes::BRICK;
  }
  for (int z = 48; z < 200; z += 8)
  {
    if (z == 96)
      z = 112;
    if (z == 128)
      z = 144;
    map[{96, z}] = blockTypes::BRICK;
    map[{104, z}] = blockTypes::BRICK;

    map[{128, z}] = blockTypes::BRICK;
    map[{136, z}] = blockTypes::BRICK;
  }
  for (int x = 48; x < 192; x += 8)
  {
    if (x == 80)
      x = 160;
    map[{x, 96}] = blockTypes::BRICK;
    map[{x, 104}] = blockTypes::BRICK;
  }
  map[{16, 104}] = blockTypes::BRICK;
  map[{24, 104}] = blockTypes::BRICK;
  map[{16, 96}] = blockTypes::ARMOR;
  map[{24, 96}] = blockTypes::ARMOR;

  map[{208, 104}] = blockTypes::BRICK;
  map[{216, 104}] = blockTypes::BRICK;
  map[{208, 96}] = blockTypes::ARMOR;
  map[{216, 96}] = blockTypes::ARMOR;

  map[{112, 152}] = blockTypes::ARMOR;
  map[{112, 160}] = blockTypes::ARMOR;
  map[{120, 152}] = blockTypes::ARMOR;
  map[{120, 160}] = blockTypes::ARMOR;

  map[{112, 72}] = blockTypes::BRICK;
  map[{112, 80}] = blockTypes::BRICK;
  map[{120, 72}] = blockTypes::BRICK;
  map[{120, 80}] = blockTypes::BRICK;

  for (int z = 8; z < 32; z += 8)
  {
    map[{104, z}] = blockTypes::BRICK;
    map[{128, z}] = blockTypes::BRICK;
  }
  map[{112, 24}] = blockTypes::BRICK;
  map[{120, 24}] = blockTypes::BRICK;
  
  // border
  for (int x = 16; x < 224; x += 8)
  {
    map[{x, 0}] = blockTypes::BORDER; // низ
    map[{x, 216}] = blockTypes::BORDER; // верх
  }
  for (int z = 0; z < 224; z += 8)
  {
    map[{0, z}] = blockTypes::BORDER; // слева
    map[{8, z}] = blockTypes::BORDER;

    map[{224, z}] = blockTypes::BORDER; // справа
    map[{232, z}] = blockTypes::BORDER;
    map[{240, z}] = blockTypes::BORDER;
    map[{248, z}] = blockTypes::BORDER;
  }

  for (int x = 0; x < MAP_X_SIZE * 8; x += 8)
    for (int z = 0; z < MAP_Z_SIZE * 8; z += 8)
      if ( map.find({x, z}) != map.end() )
        scene->addChild(new tile(x, 0, z, blockTex[map[{x, z}]]));
}