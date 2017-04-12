#include "viewer.h"
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <list>
#include <osgUtil/Optimizer>

std::list<osg::Node*> toDelete;

viewerThread::viewerThread()
  : _viewer(new osgViewer::Viewer)
{
  osgUtil::Optimizer opt; // ALL_OPTIMIZATIONS
  _scene = createScene(); //DEFAULT_OPTIMIZATIONS
  opt.optimize(_scene, 
    osgUtil::Optimizer::FLATTEN_STATIC_TRANSFORMS |
    osgUtil::Optimizer::REMOVE_REDUNDANT_NODES |
    osgUtil::Optimizer::REMOVE_LOADED_PROXY_NODES |
    osgUtil::Optimizer::COMBINE_ADJACENT_LODS |
    osgUtil::Optimizer::SHARE_DUPLICATE_STATE |
    osgUtil::Optimizer::MERGE_GEOMETRY |
    osgUtil::Optimizer::CHECK_GEOMETRY |
    osgUtil::Optimizer::MAKE_FAST_GEOMETRY |
    osgUtil::Optimizer::SPATIALIZE_GROUPS |
    osgUtil::Optimizer::COPY_SHARED_NODES |
    //osgUtil::Optimizer::TRISTRIP_GEOMETRY | // разделяет на triangle strips
    osgUtil::Optimizer::TESSELLATE_GEOMETRY |
    osgUtil::Optimizer::OPTIMIZE_TEXTURE_SETTINGS |
    osgUtil::Optimizer::MERGE_GEODES |
    osgUtil::Optimizer::FLATTEN_BILLBOARDS |
    //osgUtil::Optimizer::TEXTURE_ATLAS_BUILDER | // текстуры танков артефачат
    osgUtil::Optimizer::STATIC_OBJECT_DETECTION |
    osgUtil::Optimizer::FLATTEN_STATIC_TRANSFORMS_DUPLICATING_SHARED_SUBGRAPHS |
    //osgUtil::Optimizer::INDEX_MESH | // разделяет на triangles
    osgUtil::Optimizer::VERTEX_POSTTRANSFORM |
    osgUtil::Optimizer::VERTEX_PRETRANSFORM
    );
  _viewer->setUpViewInWindow(200, 400, 800, 700);
  _viewer->addEventHandler(this);
  _viewer->setSceneData(_scene);
  //_viewer->getCamera()->setCullingMode(0); // +3 fps !!!11
  _viewer->getCamera()->setClearColor(osg::Vec4(0, 0, 0, 1));
  _viewer->getCamera()->
    setViewMatrixAsLookAt({ 128, -440, 112 }, { 128, 0, 112 }, { 0, 0, 1 });
  _viewer->getCamera()->setProjectionMatrixAsPerspective(28,32./28,1,2);
  //_viewer->setCameraManipulator(new osgGA::TrackballManipulator);
  //_viewer->addEventHandler(new osgViewer::StatsHandler());
  //_viewer->setRunMaxFrameRate(1); // ограничение кол-ва кадров в сек.
}

// вьювер запускается в отдельном потоке
void viewerThread::run()
{
  while (!_viewer->done())
  {
    _viewer->frame();
    while (!toDelete.empty())
    {
      toDelete.front()->getParent(0)->removeChild(toDelete.front());
      toDelete.pop_front();
    }
  }
  //_viewer->run();
  //emit closeGUI();
}

void viewerThread::close()
{
  _viewer->setDone(true);
}

osg::ref_ptr<osg::Group> viewerThread::createScene()
{
  osg::ref_ptr<osg::Group> scene = new osg::Group;
  scene->setName("main scene");
  void createMap(osg::ref_ptr<osg::Group> scene);
  createMap(scene);
  _p1Tank = new tank(80, 8, "yellow/T1_");
  scene->addChild(_p1Tank);
  _p1Tank->setName(scene->getName() + " - 1st player tank");
  _p2Tank = new tank(144, 200, "green/T1_");
  scene->addChild(_p2Tank);
  _p2Tank->setName(scene->getName() + " - 2nd player tank");
  _p1Tank->setEnemy(_p2Tank.get());
  _p2Tank->setEnemy(_p1Tank.get());
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
          _pressedKeysP1[119] = true;
          _p1Tank->moveTo(direction::UP);
          break;
        }
        case(115) : // S
        {
          _pressedKeysP1[115] = true;
          _p1Tank->moveTo(direction::DOWN);
          break;
        }
        case(97) : // A
        {
          _pressedKeysP1[97] = true;
          _p1Tank->moveTo(direction::LEFT);
          break;
        }
        case(100) : // D
        {
          _pressedKeysP1[100] = true;
          _p1Tank->moveTo(direction::RIGHT);
          break;
        }
        case(32) : // SPACE
        {
          _p1Tank->shoot();
          break;
        }
        ////////////////////////////////////////////////////////////
        case(osgGA::GUIEventAdapter::KEY_Up) : // up
        {
          _pressedKeysP2[65362] = true;
          _p2Tank->moveTo(direction::UP);
          break;
        }
        case(osgGA::GUIEventAdapter::KEY_Down) : // down
        {
          _pressedKeysP2[65364] = true;
          _p2Tank->moveTo(direction::DOWN);
          break;
        }
        case(osgGA::GUIEventAdapter::KEY_Left) : // left
        {
          _pressedKeysP2[65361] = true;
          _p2Tank->moveTo(direction::LEFT);
          break;
        }
        case(osgGA::GUIEventAdapter::KEY_Right) : // right
        {
          _pressedKeysP2[65363] = true;
          _p2Tank->moveTo(direction::RIGHT);
          break;
        }
        case(osgGA::GUIEventAdapter::KEY_KP_Insert) : // num0
        {
          _p2Tank->shoot();
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
          _pressedKeysP1[key] = false;
          // если это была единственная нажатая клавиша то танк останавливается
          if (_pressedKeysP1[119])
            _p1Tank->moveTo(direction::UP);
          else if (_pressedKeysP1[115])
            _p1Tank->moveTo(direction::DOWN);
          else if (_pressedKeysP1[97])
            _p1Tank->moveTo(direction::LEFT);
          else if (_pressedKeysP1[100])
            _p1Tank->moveTo(direction::RIGHT);
          else
            _p1Tank->stop();
          break;
        }
        case(65362) : // up
        case(65364) : // down
        case(65361) : // left
        case(65363) : // right
        {
          _pressedKeysP2[key] = false;
          // если это была единственная нажатая клавиша то танк останавливается
          if (_pressedKeysP2[65362])
            _p2Tank->moveTo(direction::UP);
          else if (_pressedKeysP2[65364])
            _p2Tank->moveTo(direction::DOWN);
          else if (_pressedKeysP2[65361])
            _p2Tank->moveTo(direction::LEFT);
          else if (_pressedKeysP2[65363])
            _p2Tank->moveTo(direction::RIGHT);
          else
            _p2Tank->stop();
          break;
        }
      }
      return true;
    }
    default:
      return false;
  }
}