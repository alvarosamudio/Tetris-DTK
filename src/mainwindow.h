#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QAudioOutput>
#include <QMediaPlayer>
#include "widget.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Widget *w;
    QMediaPlayer *m_music;
    QAudioOutput *m_audioOutput;
};

#endif // MAINWINDOW_H
