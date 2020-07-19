#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // Set dark theme style for the whole window
  setStyleSheet("background-color: #1e1e1e; color: white;");

  m_gameBoard = new GameBoard(this);
  m_nextPieceWidget = new NextPieceWidget(this);

  // Main Game Container
  if (!ui->gameContainer->layout()) {
    ui->gameContainer->setLayout(new QVBoxLayout());
  }
  ui->gameContainer->layout()->addWidget(m_gameBoard);
  ui->gameContainer->layout()->setContentsMargins(0, 0, 0, 0);

  // Concept: Place NextPieceWidget in a specific area
  if (!ui->nextContainer->layout()) {
    ui->nextContainer->setLayout(new QVBoxLayout());
  }
  ui->nextContainer->layout()->addWidget(m_nextPieceWidget);
  ui->nextContainer->layout()->setContentsMargins(5, 5, 5, 5);
  ui->nextContainer->layout()->setAlignment(Qt::AlignCenter);

  connect(m_gameBoard, &GameBoard::scoreChanged, this, &Widget::updateScore);
  connect(m_gameBoard, &GameBoard::nextPieceChanged, this,
          &Widget::updateNextPiece);
  connect(ui->startBtn, &QPushButton::clicked, this, &Widget::onStartClicked);

  // Custom styling for labels according to concept
  ui->scoreLabel->setText("SCORE\n000000000");
  ui->scoreLabel->setStyleSheet(
      "font-family: 'Monospace'; font-weight: bold; letter-spacing: 2px;");
}

Widget::~Widget() { delete ui; }

void Widget::onStartClicked() {
  m_gameBoard->startGame();
  m_gameBoard->setFocus();
  ui->startBtn->setText("RESTART");
}

void Widget::updateScore(int score) {
  // Pad with zeros like in concept 000012903
  QString scoreStr = QString("%1").arg(score, 9, 10, QChar('0'));
  ui->scoreLabel->setText(QString("SCORE\n%1").arg(scoreStr));
}

void Widget::updateNextPiece(const Tetromino &piece) {
  m_nextPieceWidget->setNextPiece(piece);
}
