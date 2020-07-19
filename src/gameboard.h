#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "tetrisgame.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

class GameBoard : public QWidget {
  Q_OBJECT
public:
  explicit GameBoard(QWidget *parent = nullptr);
  void startGame();
  void pauseGame();
  void resumeGame();

  const TetrisGame &getGame() const { return game; }

signals:
  void scoreChanged(int score);
  void nextPieceChanged(const Tetromino &piece);

protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private slots:
  void gameStep();

private:
  void drawBlock(QPainter &painter, int x, int y, TetrominoType type);
  QColor getColorForType(TetrominoType type);

  TetrisGame game;
  QTimer *timer;
  int blockSize;
};

#endif // GAMEBOARD_H
