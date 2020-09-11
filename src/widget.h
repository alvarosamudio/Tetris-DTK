#ifndef WIDGET_H
#define WIDGET_H

#include "gameboard.h"
#include "nextpiecewidget.h"
#include <QSettings>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

signals:
  void musicToggled(bool muted);

private slots:
  void onStartClicked();
  void onMuteClicked();
  void updateScore(int score);
  void updateNextPiece(const Tetromino &piece);
  void onGameOver(int score);

private:
  void loadHighScore();
  void saveHighScore(int score);

  Ui::Widget *ui;
  GameBoard *m_gameBoard;
  NextPieceWidget *m_nextPieceWidget;
  bool m_muted;
  int m_highScore;
};

#endif // WIDGET_H
