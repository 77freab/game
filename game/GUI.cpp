#include "GUI.h"

game::game(QWidget *parent)
  : QWidget(parent)
{
  _btn = new QPushButton("RESTART");
  _vLayout = new QVBoxLayout;
  _vLayout->addWidget(_btn);
  this->setLayout(_vLayout);
}
