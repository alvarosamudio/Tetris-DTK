#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QPoint>
#include <QVector>

enum class TetrominoType { None, I, J, L, O, S, T, Z };

struct Tetromino {
  TetrominoType type;
  QVector<QPoint> blocks;
  QPoint position;
  int rotation;

  static Tetromino create(TetrominoType type);
  void rotateClockwise();
};

class TetrisGame {
public:
  static const int Width = 10;
  static const int Height = 22;

  TetrisGame();

  void reset();
  bool step();
  void moveLeft();
  void moveRight();
  void rotate();
  void softDrop();
  void hardDrop();

  const QVector<QVector<TetrominoType>> &getGrid() const { return grid; }
  const Tetromino &getCurrentPiece() const { return currentPiece; }
  int getScore() const { return score; }
  bool isGameOver() const { return gameState == GameState::GameOver; }
  bool isPaused() const { return gameState == GameState::Paused; }
  void setPaused(bool paused);

private:
  enum class GameState { Running, Paused, GameOver };

  void spawnPiece();
  bool isValidPosition(const Tetromino &piece, QPoint pos) const;
  void lockPiece();
  void clearLines();

  QVector<QVector<TetrominoType>> grid;
  Tetromino currentPiece;
  Tetromino nextPiece;
  GameState gameState;
  int score;
};

#endif // TETRISGAME_H
