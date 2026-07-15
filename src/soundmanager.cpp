#include "soundmanager.h"
#include <QBuffer>
#include <QDataStream>
#include <QDir>
#include <QTemporaryFile>
#include <QtEndian>
#include <cmath>

static const double REST = 0.0;

// Note frequencies (Hz)
static const double NOTE_C4 = 261.63, NOTE_D4 = 293.66, NOTE_E4 = 329.63;
static const double NOTE_F4 = 349.23, NOTE_G4 = 392.00, NOTE_A4 = 440.00;
static const double NOTE_B4 = 493.88;
static const double NOTE_C5 = 523.25, NOTE_D5 = 587.33, NOTE_E5 = 659.25;
static const double NOTE_F5 = 698.46, NOTE_G5 = 783.99, NOTE_GS5 = 830.61;
static const double NOTE_A5 = 880.00;
static const double NOTE_B5 = 987.77;
static const double NOTE_C3 = 130.81, NOTE_D3 = 146.83, NOTE_E3 = 164.81;
static const double NOTE_F3 = 174.61, NOTE_G3 = 196.00, NOTE_A3 = 220.00;
static const double NOTE_GS3 = 207.65;
static const double NOTE_B3 = 246.94;

// Generate a square wave (classic 8-bit sound)
static QByteArray squareWave(double freq, int numSamples, int sampleRate) {
  QByteArray pcm;
  pcm.resize(numSamples * 2);
  for (int i = 0; i < numSamples; ++i) {
    double t = static_cast<double>(i) / sampleRate;
    double val = (sin(2.0 * M_PI * freq * t) >= 0.0) ? 0.4 : -0.4;
    // Simple envelope
    double progress = static_cast<double>(i) / numSamples;
    double env = 1.0;
    if (progress < 0.05) env = progress / 0.05;
    else if (progress > 0.85) env = (1.0 - progress) / 0.15;
    val *= env;
    qint16 s = static_cast<qint16>(val * 32767);
    qToLittleEndian<qint16>(s, reinterpret_cast<uchar*>(pcm.data() + i * 2));
  }
  return pcm;
}

static QByteArray buildWav(const QByteArray &pcmData, int sampleRate = 44100) {
  QByteArray wav;
  QDataStream stream(&wav, QIODevice::WriteOnly);
  stream.setByteOrder(QDataStream::LittleEndian);
  stream << QByteArray("RIFF");
  stream << quint32(36 + pcmData.size());
  stream << QByteArray("WAVE");
  stream << QByteArray("fmt ");
  stream << quint32(16);
  stream << quint16(1); // PCM
  stream << quint16(1); // mono
  stream << quint32(sampleRate);
  stream << quint32(sampleRate * 2);
  stream << quint16(2);
  stream << quint16(16);
  stream << QByteArray("data");
  stream << quint32(pcmData.size());
  stream.writeRawData(pcmData.constData(), pcmData.size());
  return wav;
}

static QSoundEffect *loadFromWav(const QByteArray &wavData) {
  QSoundEffect *effect = new QSoundEffect();
  QTemporaryFile tmpFile(QDir::tempPath() + "/tetris_sfx_XXXXXX.wav");
  tmpFile.setAutoRemove(false);
  if (tmpFile.open()) {
    tmpFile.write(wavData);
    tmpFile.close();
    effect->setSource(QUrl::fromLocalFile(tmpFile.fileName()));
  }
  return effect;
}

// Build a melody from note sequence {freq, durationMs}
static QByteArray buildMelodyWav(const QVector<QPair<double, int>> &notes, int sampleRate = 44100) {
  QByteArray allPcm;
  for (const auto &note : notes) {
    if (note.first > 0) {
      int samples = sampleRate * note.second / 1000;
      allPcm.append(squareWave(note.first, samples, sampleRate));
    } else {
      // Rest
      int samples = sampleRate * note.second / 1000;
      QByteArray silence(samples * 2, 0);
      allPcm.append(silence);
    }
  }
  return buildWav(allPcm, sampleRate);
}

void SoundManager::buildMelody() {
  // Korobeiniki (Tetris Theme A) - classic 8-bit arrangement
  // Quarter note = 200ms, eighth = 100ms, half = 400ms, whole = 800ms
  int q = 200, e = 100, h = 400, w = 800, dq = 300;

  m_melody = {
    // Line 1
    {NOTE_E5, q}, {NOTE_B4, e}, {NOTE_C5, e}, {NOTE_D5, q}, {NOTE_C5, e}, {NOTE_B4, e},
    {NOTE_A4, q}, {NOTE_A4, e}, {NOTE_C5, e}, {NOTE_E5, q}, {NOTE_D5, e}, {NOTE_C5, e},
    {NOTE_B4, dq}, {NOTE_C5, e}, {NOTE_D5, q}, {NOTE_E5, q},
    {NOTE_C5, q}, {NOTE_A4, q}, {NOTE_A4, q}, {REST, e},

    // Line 2
    {REST, e}, {NOTE_D5, q}, {NOTE_F5, e}, {NOTE_A5, q}, {NOTE_G5, e}, {NOTE_F5, e},
    {NOTE_E5, dq}, {NOTE_C5, e}, {NOTE_E5, q}, {NOTE_D5, e}, {NOTE_C5, e},
    {NOTE_B4, q}, {NOTE_B4, e}, {NOTE_C5, e}, {NOTE_D5, q}, {NOTE_E5, q},
    {NOTE_C5, q}, {NOTE_A4, q}, {NOTE_A4, q}, {REST, q},

    // Line 3 (bridge)
    {NOTE_E5, h}, {NOTE_C5, h},
    {NOTE_D5, h}, {NOTE_B4, h},
    {NOTE_C5, h}, {NOTE_A4, h},
    {NOTE_B4, w},

    {NOTE_E5, h}, {NOTE_C5, h},
    {NOTE_D5, h}, {NOTE_B4, h},
    {NOTE_C5, q}, {NOTE_E5, q}, {NOTE_A5, h},
    {NOTE_GS5, w},

    // Line 4 (repeat of line 1)
    {NOTE_E5, q}, {NOTE_B4, e}, {NOTE_C5, e}, {NOTE_D5, q}, {NOTE_C5, e}, {NOTE_B4, e},
    {NOTE_A4, q}, {NOTE_A4, e}, {NOTE_C5, e}, {NOTE_E5, q}, {NOTE_D5, e}, {NOTE_C5, e},
    {NOTE_B4, dq}, {NOTE_C5, e}, {NOTE_D5, q}, {NOTE_E5, q},
    {NOTE_C5, q}, {NOTE_A4, q}, {NOTE_A4, q}, {REST, e},

    // Line 5 (repeat of line 2)
    {REST, e}, {NOTE_D5, q}, {NOTE_F5, e}, {NOTE_A5, q}, {NOTE_G5, e}, {NOTE_F5, e},
    {REST, e}, {NOTE_E5, q}, {NOTE_C5, e}, {NOTE_E5, q}, {NOTE_D5, e}, {NOTE_C5, e},
    {REST, e}, {NOTE_B4, q}, {NOTE_C5, e}, {NOTE_D5, q}, {NOTE_E5, q},
    {REST, e}, {NOTE_C5, q}, {NOTE_A4, e}, {NOTE_A4, q}, {REST, q},
  };

  // Simple bass line following the melody
  m_bass = {
    {NOTE_E3, q}, {NOTE_E3, e}, {NOTE_E3, e}, {NOTE_E3, q}, {NOTE_E3, e}, {NOTE_E3, e},
    {NOTE_A3, q}, {NOTE_A3, e}, {NOTE_A3, e}, {NOTE_A3, q}, {NOTE_A3, e}, {NOTE_A3, e},
    {NOTE_GS3, dq}, {NOTE_GS3, e}, {NOTE_GS3, q}, {NOTE_GS3, q},
    {NOTE_A3, q}, {NOTE_A3, q}, {NOTE_A3, q}, {REST, e},

    {REST, e}, {NOTE_D3, q}, {NOTE_D3, e}, {NOTE_D3, q}, {NOTE_D3, e}, {NOTE_D3, e},
    {NOTE_C3, dq}, {NOTE_C3, e}, {NOTE_C3, q}, {NOTE_C3, e}, {NOTE_C3, e},
    {NOTE_G3, q}, {NOTE_G3, e}, {NOTE_G3, e}, {NOTE_G3, q}, {NOTE_G3, q},
    {NOTE_A3, q}, {NOTE_A3, q}, {NOTE_A3, q}, {REST, q},

    {NOTE_E3, h}, {NOTE_E3, h},
    {NOTE_GS3, h}, {NOTE_GS3, h},
    {NOTE_A3, h}, {NOTE_A3, h},
    {NOTE_E3, w},

    {NOTE_E3, h}, {NOTE_E3, h},
    {NOTE_GS3, h}, {NOTE_GS3, h},
    {NOTE_A3, q}, {NOTE_E3, q}, {NOTE_E3, h},
    {NOTE_E3, w},

    {NOTE_E3, q}, {NOTE_E3, e}, {NOTE_E3, e}, {NOTE_E3, q}, {NOTE_E3, e}, {NOTE_E3, e},
    {NOTE_A3, q}, {NOTE_A3, e}, {NOTE_A3, e}, {NOTE_A3, q}, {NOTE_A3, e}, {NOTE_A3, e},
    {NOTE_GS3, dq}, {NOTE_GS3, e}, {NOTE_GS3, q}, {NOTE_GS3, q},
    {NOTE_A3, q}, {NOTE_A3, q}, {NOTE_A3, q}, {REST, e},

    {REST, e}, {NOTE_D3, q}, {NOTE_D3, e}, {NOTE_D3, q}, {NOTE_D3, e}, {NOTE_D3, e},
    {REST, e}, {NOTE_C3, q}, {NOTE_C3, e}, {NOTE_C3, q}, {NOTE_C3, e}, {NOTE_C3, e},
    {REST, e}, {NOTE_G3, q}, {NOTE_G3, e}, {NOTE_G3, q}, {NOTE_G3, q},
    {REST, e}, {NOTE_A3, q}, {NOTE_A3, e}, {NOTE_A3, q}, {REST, q},
  };
}

SoundManager::SoundManager(QObject *parent)
    : QObject(parent), m_muted(false), m_noteIndex(0) {
  // Sound effects - classic 8-bit style
  // Rotate: quick high beep
  {
    QByteArray pcm;
    int samples = 44100 * 40 / 1000;
    pcm.append(squareWave(880, samples, 44100));
    m_rotate = loadFromWav(buildWav(pcm));
  }
  // Drop: low thud
  {
    QByteArray pcm;
    pcm.append(squareWave(150, 44100 * 30 / 1000, 44100));
    pcm.append(squareWave(100, 44100 * 70 / 1000, 44100));
    m_drop = loadFromWav(buildWav(pcm));
  }
  // Line clear: ascending arpeggio
  {
    QByteArray pcm;
    int q = 44100 * 60 / 1000;
    pcm.append(squareWave(523, q, 44100));
    pcm.append(squareWave(659, q, 44100));
    pcm.append(squareWave(784, q, 44100));
    pcm.append(squareWave(1047, q * 2, 44100));
    m_lineClear = loadFromWav(buildWav(pcm));
  }
  // Game over: descending sad notes
  {
    QByteArray pcm;
    int n = 44100 * 200 / 1000;
    pcm.append(squareWave(440, n, 44100));
    pcm.append(squareWave(370, n, 44100));
    pcm.append(squareWave(311, n, 44100));
    pcm.append(squareWave(262, n * 3, 44100));
    m_gameOver = loadFromWav(buildWav(pcm));
  }

  buildMelody();

  m_musicTimer = new QTimer(this);
  connect(m_musicTimer, &QTimer::timeout, this, &SoundManager::playNextNote);
}

void SoundManager::playRotate() {
  if (!m_muted && m_rotate && m_rotate->status() != QSoundEffect::Loading)
    m_rotate->play();
}

void SoundManager::playDrop() {
  if (!m_muted && m_drop && m_drop->status() != QSoundEffect::Loading)
    m_drop->play();
}

void SoundManager::playLineClear() {
  if (!m_muted && m_lineClear && m_lineClear->status() != QSoundEffect::Loading)
    m_lineClear->play();
}

void SoundManager::playGameOver() {
  stopMusic();
  if (!m_muted && m_gameOver && m_gameOver->status() != QSoundEffect::Loading)
    m_gameOver->play();
}

void SoundManager::setMuted(bool muted) {
  m_muted = muted;
  float vol = muted ? 0.0f : 1.0f;
  if (m_rotate) m_rotate->setVolume(vol);
  if (m_drop) m_drop->setVolume(vol);
  if (m_lineClear) m_lineClear->setVolume(vol);
  if (m_gameOver) m_gameOver->setVolume(vol);
  if (muted)
    stopMusic();
}

void SoundManager::startMusic() {
  m_noteIndex = 0;
  playNextNote();
}

void SoundManager::stopMusic() {
  m_musicTimer->stop();
}

void SoundManager::playNextNote() {
  if (m_muted || m_noteIndex >= m_melody.size()) {
    if (!m_muted && m_noteIndex >= m_melody.size()) {
      m_noteIndex = 0;
      playNextNote();
    }
    return;
  }

  const auto &note = m_melody[m_noteIndex];

  // Play melody note
  if (note.freq > 0) {
    QByteArray pcm = squareWave(note.freq, 44100 * note.durationMs / 1000 * 80 / 100, 44100);
    QSoundEffect *s = loadFromWav(buildWav(pcm));
    s->setVolume(m_muted ? 0.0f : 0.3f);
    s->play();
    connect(s, &QSoundEffect::playingChanged, s, [s]() { s->deleteLater(); });
  }

  // Play bass note
  if (m_noteIndex < m_bass.size() && m_bass[m_noteIndex].freq > 0) {
    const auto &bass = m_bass[m_noteIndex];
    QByteArray pcm = squareWave(bass.freq, 44100 * bass.durationMs / 1000 * 80 / 100, 44100);
    QSoundEffect *b = loadFromWav(buildWav(pcm));
    b->setVolume(m_muted ? 0.0f : 0.15f);
    b->play();
    connect(b, &QSoundEffect::playingChanged, b, [b]() { b->deleteLater(); });
  }

  m_musicTimer->setSingleShot(true);
  m_musicTimer->start(note.durationMs);
  m_noteIndex++;
}
