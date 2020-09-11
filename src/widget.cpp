#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), m_muted(false), m_highScore(0) {
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
  connect(m_gameBoard, &GameBoard::gameOver, this, &Widget::onGameOver);
  connect(ui->startBtn, &QPushButton::clicked, this, &Widget::onStartClicked);
  connect(ui->muteBtn, &QPushButton::clicked, this, &Widget::onMuteClicked);

  // Custom styling for labels according to concept
  ui->scoreLabel->setText("SCORE\n000000");
  ui->scoreLabel->setStyleSheet(
      "font-size: 16pt; font-family: 'Monospace'; font-weight: bold; letter-spacing: 2px; color: #ffffff;");

  ui->highScoreLabel->setStyleSheet(
      "font-size: 11pt; font-family: 'Monospace'; font-weight: bold; color: #ffcc00;");

  loadHighScore();
}

Widget::~Widget() { delete ui; }

void Widget::loadHighScore() {
  QSettings settings("deepin-es", "Tetris");
  m_highScore = settings.value("highScore", 0).toInt();
  QString hsStr = QString("%1").arg(m_highScore, 6, 10, QChar('0'));
  ui->highScoreLabel->setText(QString("HI-SCORE\n%1").arg(hsStr));
}

void Widget::saveHighScore(int score) {
  QSettings settings("deepin-es", "Tetris");
  settings.setValue("highScore", score);
  settings.sync();
}

void Widget::onGameOver(int score) {
  if (score > m_highScore) {
    m_highScore = score;
    saveHighScore(score);
    QString hsStr = QString("%1").arg(m_highScore, 6, 10, QChar('0'));
    ui->highScoreLabel->setText(QString("HI-SCORE\n%1").arg(hsStr));
  }
}

void Widget::onStartClicked() {
  m_gameBoard->startGame();
  m_gameBoard->setFocus();
  ui->startBtn->setText("RESTART");
}

void Widget::updateScore(int score) {
  QString scoreStr = QString("%1").arg(score, 6, 10, QChar('0'));
  ui->scoreLabel->setText(QString("SCORE\n%1").arg(scoreStr));
}

void Widget::updateNextPiece(const Tetromino &piece) {
  m_nextPieceWidget->setNextPiece(piece);
}

void Widget::onMuteClicked() {
  m_muted = !m_muted;
  ui->muteBtn->setText(m_muted ? "Unmute" : "Mute");
  emit musicToggled(m_muted);
}
