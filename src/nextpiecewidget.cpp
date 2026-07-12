#include "nextpiecewidget.h"
#include "tetriscolors.h"
#include <QLinearGradient>
#include <QPainter>

NextPieceWidget::NextPieceWidget(QWidget *parent) : QWidget(parent) {
  setMinimumSize(80, 80);
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
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

  int blockSize = qMin(width() / 4, height() / 3);
  if (blockSize < 6) blockSize = 6;
  int offsetX = (width() - 4 * blockSize) / 2;
  int offsetY = (height() - 2 * blockSize) / 2;

  QColor color = getColorForType(m_piece.type);
  for (const QPoint &block : m_piece.blocks) {
    QRectF blockRect(offsetX + block.x() * blockSize + 1,
                     offsetY + block.y() * blockSize + 1, blockSize - 2,
                     blockSize - 2);

    QLinearGradient gradient(blockRect.topLeft(), blockRect.bottomLeft());
    gradient.setColorAt(0, color.lighter(130));
    gradient.setColorAt(1, color.darker(120));

    painter.setPen(QPen(color.darker(140), 1));
    painter.setBrush(gradient);
    painter.drawRoundedRect(blockRect, 4, 4);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255, 100));
    QRectF highlightRect(blockRect.left() + 2,
                         blockRect.top() + 1,
                         blockRect.width() * 0.4, blockRect.height() * 0.25);
    painter.drawRoundedRect(highlightRect, 2, 2);
  }
}
