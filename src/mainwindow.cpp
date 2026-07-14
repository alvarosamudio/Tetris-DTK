#include "mainwindow.h"
#include <DMainWindow>
#include <QUrl>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    w = new Widget;

    resize(410, 630);
    setMinimumSize(410, 630);
    setMaximumSize(410, 630);

    setCentralWidget(w);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

    m_audioOutput = new QAudioOutput(this);
    m_audioOutput->setVolume(0.5f);

    m_music = new QMediaPlayer(this);
    m_music->setAudioOutput(m_audioOutput);
    m_music->setSource(QUrl(QStringLiteral("qrc:/tetris_theme.wav")));
    m_music->setLoops(QMediaPlayer::Infinite);
    m_music->play();

    connect(w, &Widget::musicToggled, this, [this](bool muted) {
        m_audioOutput->setMuted(muted);
    });
}

MainWindow::~MainWindow()
{
}
