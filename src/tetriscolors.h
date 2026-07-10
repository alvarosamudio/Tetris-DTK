#ifndef TETRISCOLORS_H
#define TETRISCOLORS_H

#include "tetrisgame.h"
#include <QColor>

inline QColor getColorForType(TetrominoType type) {
  switch (type) {
  case TetrominoType::I: return QColor(255, 80, 80);
  case TetrominoType::J: return QColor(80, 150, 255);
  case TetrominoType::L: return QColor(255, 150, 50);
  case TetrominoType::O: return QColor(255, 220, 50);
  case TetrominoType::S: return QColor(100, 220, 80);
  case TetrominoType::T: return QColor(180, 100, 255);
  case TetrominoType::Z: return QColor(255, 100, 100);
  default: return Qt::black;
  }
}

#endif // TETRISCOLORS_H
