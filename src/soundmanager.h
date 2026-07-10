#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
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

private:
  QSoundEffect *m_rotate;
  QSoundEffect *m_drop;
  QSoundEffect *m_lineClear;
  QSoundEffect *m_gameOver;
};

#endif // SOUNDMANAGER_H
