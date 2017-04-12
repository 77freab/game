#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "viewer.h"

class game : public QWidget
{
  Q_OBJECT
public:
  game(QWidget *parent = Q_NULLPTR);
  ~game();
  osg::ref_ptr<viewerThread> _myViewer;
signals:
  void closeViewer();
private slots:
  void start();
private:
  QPushButton* _btn;
  QVBoxLayout* _vLayout;
};
