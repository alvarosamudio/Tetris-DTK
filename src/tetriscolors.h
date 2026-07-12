#ifndef TETRISCOLORS_H
#define TETRISCOLORS_H

#include "tetrisgame.h"
#include <QColor>

inline QColor getColorForType(TetrominoType type) {
  switch (type) {
  case TetrominoType::I: return QColor(0, 220, 255);
  case TetrominoType::J: return QColor(30, 100, 255);
  case TetrominoType::L: return QColor(255, 140, 0);
  case TetrominoType::O: return QColor(255, 210, 0);
  case TetrominoType::S: return QColor(80, 210, 50);
  case TetrominoType::T: return QColor(180, 60, 255);
  case TetrominoType::Z: return QColor(240, 40, 60);
  default: return Qt::black;
  }
}

#endif // TETRISCOLORS_H
