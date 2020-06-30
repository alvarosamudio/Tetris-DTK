#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  m_gameBoard = new GameBoard(this);

  // Create a layout for the gameContainer if it doesn't have one
  if (!ui->gameContainer->layout()) {
    ui->gameContainer->setLayout(new QVBoxLayout());
  }
  ui->gameContainer->layout()->addWidget(m_gameBoard);
  ui->gameContainer->layout()->setContentsMargins(0, 0, 0, 0);

  connect(ui->startBtn, &QPushButton::clicked, this, &Widget::onStartClicked);
}

Widget::~Widget() { delete ui; }

void Widget::onStartClicked() {
  m_gameBoard->startGame();
  m_gameBoard->setFocus();
  ui->startBtn->setText("Restart");
}
