#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

     a.setAttribute(Qt::AA_UseHighDpiPixmaps);
     a.setOrganizationName("deepinenespañol");
     a.setApplicationVersion(DApplication::buildVersion("1.0"));
     a.setApplicationAcknowledgementPage("https://deepinenespañol.org");
     a.setApplicationDescription("tetris in dtk");
     //a.setProductIcon(QIcon(":/images/icon.svg"));
     //a.setProductName("Tetris");
     a.setApplicationName("Tetris");


    MainWindow w;
    w.setMinimumSize(100,560);
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.show();

    Dtk::Widget::moveToCenter(&w);


    return a.exec();
}
