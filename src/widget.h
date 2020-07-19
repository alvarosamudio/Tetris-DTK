#ifndef WIDGET_H
#define WIDGET_H

#include "gameboard.h"
#include "nextpiecewidget.h"
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
  void updateScore(int score);
  void updateNextPiece(const Tetromino &piece);

private:
  Ui::Widget *ui;
  GameBoard *m_gameBoard;
  NextPieceWidget *m_nextPieceWidget;
};

#endif // WIDGET_H
