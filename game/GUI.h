#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class game : public QWidget
{
  Q_OBJECT
public:
  game(QWidget *parent = Q_NULLPTR);
private:
  QPushButton* _btn;
  QVBoxLayout* _vLayout;
};
