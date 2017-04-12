#include "GUI.h"

game::game(QWidget *parent)
  : QWidget(parent)
{
  _btn = new QPushButton("RESTART");
  _vLayout = new QVBoxLayout;
  _vLayout->addWidget(_btn);
  this->setLayout(_vLayout);
  connect(_btn, &QPushButton::clicked, this, &game::start);
}

game::~game()
{
  emit closeViewer();
  if (_myViewer != nullptr)
    _myViewer->wait();
}

void game::start()
{
  if (_myViewer != nullptr)
  {
    emit closeViewer();
    _myViewer->wait();
  }
  _myViewer = new viewerThread;
  connect(_myViewer, &viewerThread::closeGUI, this, &game::close);
  connect(this, &game::closeViewer, _myViewer, &viewerThread::close);
  _myViewer->start();
}
