#include "mainwindow.h"
#include <DMainWindow>
#include <QtWidgets/QVBoxLayout>


DWIDGET_USE_NAMESPACE


MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)


{
    w = new Widget;

    resize(w->size());

    setCentralWidget(w);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

MainWindow::~MainWindow()
{

}
