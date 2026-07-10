#include "nextpiecewidget.h"
#include "tetriscolors.h"
#include <QLinearGradient>
#include <QPainter>

NextPieceWidget::NextPieceWidget(QWidget *parent) : QWidget(parent) {
  setFixedSize(80, 120);
}

void NextPieceWidget::setNextPiece(const Tetromino &piece) {
  m_piece = piece;
  update();
}

void NextPieceWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setBrush(QColor(35, 35, 35));
  painter.setPen(Qt::NoPen);
  painter.drawRoundedRect(rect(), 20, 20);

  if (m_piece.type == TetrominoType::None)
    return;

  int blockSize = 18;
  int offsetX = (width() - 4 * blockSize) / 2;
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

    painter.setBrush(QColor(255, 255, 255, 130));
    QRectF highlightRect(blockRect.left() + blockRect.width() * 0.25,
                         blockRect.top() + blockRect.height() * 0.15,
                         blockRect.width() * 0.5, blockRect.height() * 0.25);
    painter.drawRoundedRect(highlightRect, highlightRect.height() / 2.0,
                            highlightRect.height() / 2.0);
  }
}
