#include "mainwindow.h"
#include <DAboutDialog>
#include <DApplication>
#include <DWidgetUtil>
#include <QApplication>
#include <QDir>
#include <QTranslator>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.loadTranslator();
    a.setOrganizationName("deepin en español");

    QTranslator appTranslator;
    appTranslator.load(QLocale(), QLatin1String("tetris"), QLatin1String("_"),
                       QLatin1String(":/translations/"));
    a.installTranslator(&appTranslator);
    a.setProductIcon(QIcon::fromTheme("applications-games"));
    a.setWindowIcon(QIcon::fromTheme("applications-games"));
    a.setProductName(QApplication::translate("main", "Tetris"));
    a.setApplicationName("Tetris");

    DAboutDialog dialog;
    a.setAboutDialog(&dialog);
    dialog.setWindowTitle("Tetris");
    dialog.setProductName("<span>Tetris</span>");
    dialog.setProductIcon(QIcon::fromTheme("applications-games"));
    dialog.setDescription(
        "<span style=' font-size:8pt; font-weight:600;'>Deepin en Español </span>"
        "<a href='https://deepinenespanol.org'>https://deepinenespanol.org</a><br/>"
        "<span style=' font-size:8pt; font-weight:600;'>Deepin Latin Code - developers</span>");
    dialog.setVersion(DApplication::buildVersion("Version 0.1"));
    dialog.setWebsiteName("deepinenespanol.org");
    dialog.setWebsiteLink("https://deepinenespanol.org");

    MainWindow w;
    w.show();
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
