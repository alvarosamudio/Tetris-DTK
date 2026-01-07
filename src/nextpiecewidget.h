#ifndef NEXTPIECEWIDGET_H
#define NEXTPIECEWIDGET_H

#include "tetrisgame.h"
#include <QLinearGradient>
#include <QPainter>
#include <QWidget>

class NextPieceWidget : public QWidget {
  Q_OBJECT
public:
  explicit NextPieceWidget(QWidget *parent = nullptr) : QWidget(parent) {
    setFixedSize(80, 120);
  }

  void setNextPiece(const Tetromino &piece) {
    m_piece = piece;
    update();
  }

protected:
  void paintEvent(QPaintEvent *) override {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Styling from concept: Vertical dark box with rounded corners
    painter.setBrush(QColor(35, 35, 35));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 20, 20);

    if (m_piece.type == TetrominoType::None)
      return;

    int blockSize = 18;
    // Center the piece
    int offsetX = (width() - 4 * blockSize) / 2;
    if (m_piece.type == TetrominoType::I)
      offsetX = (width() - 4 * blockSize) / 2;
    int offsetY = (height() - 2 * blockSize) / 2;

    QColor color = getColorForType(m_piece.type);
    for (const QPoint &block : m_piece.blocks) {
      QRectF blockRect(offsetX + block.x() * blockSize + 2,
                       offsetY + block.y() * blockSize + 2, blockSize - 4,
                       blockSize - 4);

      QLinearGradient gradient(blockRect.topLeft(), blockRect.bottomLeft());
      gradient.setColorAt(0, color.lighter(130));
      gradient.setColorAt(1, color.darker(110));

      painter.setBrush(gradient);
      painter.drawRoundedRect(blockRect, blockRect.width() / 2.0,
                              blockRect.height() / 2.0);

      // Highlight
      painter.setBrush(QColor(255, 255, 255, 130));
      QRectF highlightRect(blockRect.left() + blockRect.width() * 0.25,
                           blockRect.top() + blockRect.height() * 0.15,
                           blockRect.width() * 0.5, blockRect.height() * 0.25);
      painter.drawRoundedRect(highlightRect, highlightRect.height() / 2.0,
                              highlightRect.height() / 2.0);
    }
  }

private:
  QColor getColorForType(TetrominoType type) {
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

  Tetromino m_piece;
};

#endif // NEXTPIECEWIDGET_H
