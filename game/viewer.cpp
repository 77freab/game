#include "viewer.h"

viewerThread::viewerThread()
  : _viewer(new osgViewer::Viewer)
{
  _scene = createScene();
  _viewer->setUpViewInWindow(200, 400, 800, 700);
  _viewer->addEventHandler(this);
  _viewer->setSceneData(_scene);
  //_viewer->addEventHandler(new osgViewer::StatsHandler());
  //_viewer->setRunMaxFrameRate(1); // ограничение кол-ва кадров в сек.
}

// вьювер запускается в отдельном потоке
void viewerThread::run()
{
  _viewer->run();
}

osg::ref_ptr<osg::Group> viewerThread::createScene()
{
  osg::ref_ptr<osg::Group> scene = new osg::Group;
  scene->setName("main scene");
  void createMap(osg::ref_ptr<osg::Group> scene);
  createMap(scene);
  _tank = new tank(80, 8, "yellow/T1_");
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
          // если это была единственная нажатая клавиша то танк останавливается
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