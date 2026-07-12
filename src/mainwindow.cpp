#include "mainwindow.h"
#include <DMainWindow>
#include <QUrl>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    w = new Widget;

    resize(520, 780);
    setMinimumSize(380, 500);

    setCentralWidget(w);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

    m_playlist = new QMediaPlaylist(this);
    m_playlist->addMedia(QUrl("qrc:/tetris_theme.wav"));
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    m_music = new QMediaPlayer(this);
    m_music->setPlaylist(m_playlist);
    m_music->play();

    connect(w, &Widget::musicToggled, this, [this](bool muted) {
        m_music->setMuted(muted);
    });
}

MainWindow::~MainWindow()
{
}
