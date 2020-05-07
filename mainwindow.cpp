#include "mainwindow.h"
#include <QWidget>
#include <DMainWindow>


DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    w = new Widget;

    resize(w->size());
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{

}
