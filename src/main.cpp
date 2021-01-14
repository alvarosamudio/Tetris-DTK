#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>  //Dtk::Widget::moveToCenter(&w)
#include <DAboutDialog>
#include <DMainWindow>


DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();  //让bar处在标题栏中
    DApplication a(argc, argv);
    DAboutDialog dialog;

     //a.setAttribute(Qt::AA_UseHighDpiPixmaps);
     a.loadTranslator();
     a.setOrganizationName("deepin en español");
     //a.setApplicationVersion(DApplication::buildVersion("0.1a"));
     //a.setApplicationAcknowledgementPage("https://");
     a.setProductIcon(QIcon(":/images/pixlr_logo.svg"));
     a.setWindowIcon(QIcon(":/images/pixlr_logo.svg"));
     a.setProductName("Tetris");
     a.setApplicationName("Tetris");

     //Dialog//
     a.setAboutDialog(&dialog);
     //Title
      dialog.setWindowTitle("Tetris");
      dialog.setProductName("<span>Tetris</span>");
      dialog.setProductIcon(QIcon(":/images/logo.svg"));
      //dialog.setCompanyLogo(QPixmap(":/images/logo.svg"));
      dialog.setDescription(
          "<span style=' font-size:8pt; font-weight:600;'>Deepin en Español </span>"
          "<a href='https://deepinenespañol.org'>https://deepinenespañol.org</a><br/>"
          "<span style=' font-size:8pt; font-weight:600;'>Deepin Latin Code - developers</span>");
      dialog.setVersion(DApplication::buildVersion("Version 0.1"));
      dialog.setWebsiteName("deepinenespañol.org");
      dialog.setWebsiteLink("https://deepinenespañol.org");

    MainWindow w;
    //Widget w;
//    w.setTranslucentBackground(100);
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.show();

    //Centrando ventana

    Dtk::Widget::moveToCenter(&w);


    return a.exec();
}
