#ifndef NEXTPIECEWIDGET_H
#define NEXTPIECEWIDGET_H

#include "tetrisgame.h"
#include <QWidget>

class NextPieceWidget : public QWidget {
  Q_OBJECT
public:
  explicit NextPieceWidget(QWidget *parent = nullptr);

  void setNextPiece(const Tetromino &piece);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QColor getColorForType(TetrominoType type);

  Tetromino m_piece;
};

#endif // NEXTPIECEWIDGET_H
