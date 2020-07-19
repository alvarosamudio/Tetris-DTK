#include "gameboard.h"
#include <QKeyEvent>
#include <QLinearGradient>
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
  emit scoreChanged(game.getScore());
  emit nextPieceChanged(game.getNextPiece());
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
  int oldScore = game.getScore();
  TetrominoType oldNextType = game.getNextPiece().type;

  if (!game.step()) {
    timer->stop();
  }

  if (game.getScore() != oldScore) {
    emit scoreChanged(game.getScore());
  }
  if (game.getNextPiece().type != oldNextType) {
    emit nextPieceChanged(game.getNextPiece());
  }

  update();
}

void GameBoard::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // Background - Concept Dark theme
  painter.fillRect(rect(), QColor(25, 25, 25));

  // Watermark "deepin"
  painter.setOpacity(0.05);
  painter.setPen(Qt::white);
  QFont font = painter.font();
  font.setPointSize(45);
  font.setBold(true);
  painter.setFont(font);
  painter.drawText(rect(), Qt::AlignCenter, "deepin");
  painter.setOpacity(1.0);

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
    painter.fillRect(rect(), QColor(0, 0, 0, 180));
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
  } else if (game.isPaused()) {
    painter.fillRect(rect(), QColor(0, 0, 0, 120));
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "PAUSED");
  }
}

void GameBoard::drawBlock(QPainter &painter, int x, int y, TetrominoType type) {
  QColor color = getColorForType(type);
  QRectF blockRect(x * blockSize + 3, y * blockSize + 3, blockSize - 6,
                   blockSize - 6);

  QLinearGradient gradient(blockRect.topLeft(), blockRect.bottomLeft());
  gradient.setColorAt(0, color.lighter(140));
  gradient.setColorAt(1, color.darker(110));

  painter.setPen(Qt::NoPen);
  painter.setBrush(gradient);

  // Pill shape
  painter.drawRoundedRect(blockRect, blockRect.width() / 2.0,
                          blockRect.height() / 2.0);

  // Concept Highlight
  painter.setBrush(QColor(255, 255, 255, 130));
  QRectF highlightRect(blockRect.left() + blockRect.width() * 0.25,
                       blockRect.top() + blockRect.height() * 0.15,
                       blockRect.width() * 0.5, blockRect.height() * 0.25);
  painter.drawRoundedRect(highlightRect, highlightRect.height() / 2.0,
                          highlightRect.height() / 2.0);
}

QColor GameBoard::getColorForType(TetrominoType type) {
  switch (type) {
  case TetrominoType::I:
    return QColor(255, 80, 80);
  case TetrominoType::J:
    return QColor(80, 150, 255);
  case TetrominoType::L:
    return QColor(255, 150, 50);
  case TetrominoType::O:
    return QColor(255, 220, 50);
  case TetrominoType::S:
    return QColor(100, 220, 80);
  case TetrominoType::T:
    return QColor(180, 100, 255);
  case TetrominoType::Z:
    return QColor(255, 100, 100);
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
