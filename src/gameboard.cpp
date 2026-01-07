#include "gameboard.h"
#include <QKeyEvent>
#include <QPainter>

GameBoard::GameBoard(QWidget *parent) : QWidget(parent), blockSize(30) {
  setFocusPolicy(Qt::StrongFocus);
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameBoard::gameStep);
  setFixedSize(TetrisGame::Width * blockSize,
               (TetrisGame::Height - 2) * blockSize);
}

void GameBoard::startGame() {
  game.reset();
  timer->start(500);
  update();
}

void GameBoard::pauseGame() {
  game.setPaused(true);
  timer->stop();
  update();
}

void GameBoard::resumeGame() {
  game.setPaused(false);
  timer->start(500);
  update();
}

void GameBoard::gameStep() {
  if (!game.step()) {
    timer->stop();
  }
  update();
}

void GameBoard::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.fillRect(rect(), Qt::black);

  const auto &grid = game.getGrid();
  for (int y = 2; y < TetrisGame::Height; ++y) {
    for (int x = 0; x < TetrisGame::Width; ++x) {
      if (grid[y][x] != TetrominoType::None) {
        drawBlock(painter, x, y - 2, grid[y][x]);
      }
    }
  }

  const auto &piece = game.getCurrentPiece();
  for (const QPoint &block : piece.blocks) {
    int x = piece.position.x() + block.x();
    int y = piece.position.y() + block.y();
    if (y >= 2) {
      drawBlock(painter, x, y - 2, piece.type);
    }
  }

  if (game.isGameOver()) {
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
  } else if (game.isPaused()) {
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "PAUSED");
  }
}

void GameBoard::drawBlock(QPainter &painter, int x, int y, TetrominoType type) {
  QColor color = getColorForType(type);
  painter.fillRect(x * blockSize, y * blockSize, blockSize - 1, blockSize - 1,
                   color);
  painter.setPen(color.lighter());
  painter.drawRect(x * blockSize, y * blockSize, blockSize - 1, blockSize - 1);
}

QColor GameBoard::getColorForType(TetrominoType type) {
  switch (type) {
  case TetrominoType::I:
    return Qt::cyan;
  case TetrominoType::J:
    return Qt::blue;
  case TetrominoType::L:
    return QColor(255, 165, 0); // Orange
  case TetrominoType::O:
    return Qt::yellow;
  case TetrominoType::S:
    return Qt::green;
  case TetrominoType::T:
    return Qt::magenta;
  case TetrominoType::Z:
    return Qt::red;
  default:
    return Qt::black;
  }
}

void GameBoard::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Left:
    game.moveLeft();
    break;
  case Qt::Key_Right:
    game.moveRight();
    break;
  case Qt::Key_Up:
    game.rotate();
    break;
  case Qt::Key_Down:
    game.softDrop();
    break;
  case Qt::Key_Space:
    game.hardDrop();
    break;
  case Qt::Key_P:
    if (game.isPaused())
      resumeGame();
    else
      pauseGame();
    break;
  default:
    QWidget::keyPressEvent(event);
    return;
  }
  update();
}
