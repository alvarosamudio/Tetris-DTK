#ifndef WIDGET_H
#define WIDGET_H

#include "gameboard.h"
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private slots:
  void onStartClicked();

private:
  Ui::Widget *ui;
  GameBoard *m_gameBoard;
};

#endif // WIDGET_H
