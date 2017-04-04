#include <game.h>

void createMap(osg::ref_ptr<osg::Group> scene)
{
  for (int i = -80; i <= -32; i += 8)
  {
    scene->addChild(new tile(-80, 0, i, "brick.png"));
    scene->addChild(new tile(-72, 0, i, "brick.png"));

    scene->addChild(new tile(-48, 0, i, "brick.png"));
    scene->addChild(new tile(-40, 0, i, "brick.png"));

    scene->addChild(new tile(48, 0, i, "brick.png"));
    scene->addChild(new tile(56, 0, i, "brick.png"));

    scene->addChild(new tile(80, 0, i, "brick.png"));
    scene->addChild(new tile(88, 0, i, "brick.png"));
  }
  for (int i = -56; i <= -16; i += 8)
  {
    scene->addChild(new tile(-16, 0, i, "brick.png"));
    scene->addChild(new tile(-8, 0, i, "brick.png"));

    scene->addChild(new tile(16, 0, i, "brick.png"));
    scene->addChild(new tile(24, 0, i, "brick.png"));
  }
  for (int i = 24; i <= 88; i += 8)
  {
    scene->addChild(new tile(-80, 0, i, "brick.png"));
    scene->addChild(new tile(-72, 0, i, "brick.png"));

    scene->addChild(new tile(-48, 0, i, "brick.png"));
    scene->addChild(new tile(-40, 0, i, "brick.png"));

    scene->addChild(new tile(48, 0, i, "brick.png"));
    scene->addChild(new tile(56, 0, i, "brick.png"));

    scene->addChild(new tile(80, 0, i, "brick.png"));
    scene->addChild(new tile(88, 0, i, "brick.png"));
  }
  for (int i = 40; i <= 88; i += 8)
  {
    scene->addChild(new tile(-16, 0, i, "brick.png"));
    scene->addChild(new tile(-8, 0, i, "brick.png"));

    scene->addChild(new tile(16, 0, i, "brick.png"));
    scene->addChild(new tile(24, 0, i, "brick.png"));
  }
  for (int i = -64; i <= -40; i += 8)
  {
    scene->addChild(new tile(i, 0, 0, "brick.png"));
    scene->addChild(new tile(i, 0, -8, "brick.png"));
  }
  for (int i = 48; i <= 72; i += 8)
  {
    scene->addChild(new tile(i, 0, 0, "brick.png"));
    scene->addChild(new tile(i, 0, -8, "brick.png"));
  }
  scene->addChild(new tile(-96, 0, 0, "brick.png"));
  scene->addChild(new tile(-88, 0, 0, "brick.png"));
  scene->addChild(new tile(-96, 0, -8, "armor.png"));
  scene->addChild(new tile(-88, 0, -8, "armor.png"));

  scene->addChild(new tile(96, 0, 0, "brick.png"));
  scene->addChild(new tile(104, 0, 0, "brick.png"));
  scene->addChild(new tile(96, 0, -8, "armor.png"));
  scene->addChild(new tile(104, 0, -8, "armor.png"));

  scene->addChild(new tile(0, 0, 48, "armor.png"));
  scene->addChild(new tile(0, 0, 56, "armor.png"));
  scene->addChild(new tile(8, 0, 48, "armor.png"));
  scene->addChild(new tile(8, 0, 56, "armor.png"));

  scene->addChild(new tile(-16, 0, 8, "brick.png"));
  scene->addChild(new tile(-16, 0, 16, "brick.png"));
  scene->addChild(new tile(-8, 0, 8, "brick.png"));
  scene->addChild(new tile(-8, 0, 16, "brick.png"));

  scene->addChild(new tile(16, 0, 8, "brick.png"));
  scene->addChild(new tile(16, 0, 16, "brick.png"));
  scene->addChild(new tile(24, 0, 8, "brick.png"));
  scene->addChild(new tile(24, 0, 16, "brick.png"));

  scene->addChild(new tile(0, 0, -32, "brick.png"));
  scene->addChild(new tile(0, 0, -24, "brick.png"));
  scene->addChild(new tile(8, 0, -32, "brick.png"));
  scene->addChild(new tile(8, 0, -24, "brick.png"));

  for (int i = -96; i <= -80; i += 8)
  {
    scene->addChild(new tile(-8, 0, i, "brick.png"));
    scene->addChild(new tile(16, 0, i, "brick.png"));
  }
  scene->addChild(new tile(0, 0, -80, "brick.png"));
  scene->addChild(new tile(8, 0, -80, "brick.png"));
  
  // border
  for (int i = -112; i <= 136; i += 8)
  {
    scene->addChild(new tile(i, 0, 112, "grey.png"));
    scene->addChild(new tile(i, 0, -104, "grey.png"));
  }
  for (int i = -96; i <= 104; i += 8)
  {
    scene->addChild(new tile(-112, 0, i, "grey.png"));
    scene->addChild(new tile(-104, 0, i, "grey.png"));

    scene->addChild(new tile(112, 0, i, "grey.png"));
    scene->addChild(new tile(120, 0, i, "grey.png"));
    scene->addChild(new tile(128, 0, i, "grey.png"));
    scene->addChild(new tile(136, 0, i, "grey.png"));
  }
}