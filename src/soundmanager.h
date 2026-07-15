#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QTimer>
#include <QUrl>
#include <QVector>

class SoundManager : public QObject {
  Q_OBJECT
public:
  explicit SoundManager(QObject *parent = nullptr);

  void playRotate();
  void playDrop();
  void playLineClear();
  void playGameOver();
  void setMuted(bool muted);
  void startMusic();
  void stopMusic();

private:
  QSoundEffect *m_rotate;
  QSoundEffect *m_drop;
  QSoundEffect *m_lineClear;
  QSoundEffect *m_gameOver;

  QTimer *m_musicTimer;
  bool m_muted;
  int m_noteIndex;

  struct MusicNote {
    double freq;
    int durationMs;
    MusicNote(double f, int d) : freq(f), durationMs(d) {}
  };
  QVector<MusicNote> m_melody;
  QVector<MusicNote> m_bass;
  void buildMelody();
  void playNextNote();
};

#endif // SOUNDMANAGER_H
