#include "soundmanager.h"
#include <QAudioFormat>
#include <QBuffer>
#include <QDataStream>
#include <QDir>
#include <QTemporaryFile>
#include <QtEndian>
#include <cmath>

static QByteArray generateTone(const QVector<double> &freqs, int durationMs,
                               int sampleRate = 44100) {
  int numSamples = sampleRate * durationMs / 1000;
  QByteArray pcmData;
  pcmData.resize(numSamples * 2); // 16-bit mono

  for (int i = 0; i < numSamples; ++i) {
    double t = static_cast<double>(i) / sampleRate;
    double sample = 0.0;
    double mixWeight = 1.0 / freqs.size();

    for (double freq : freqs)
      sample += mixWeight * sin(2.0 * M_PI * freq * t);

    // Apply envelope (attack 10ms, decay to sustain, release last 20ms)
    double env = 1.0;
    double attackEnd = 0.01;
    double releaseStart = durationMs / 1000.0 - 0.02;
    if (t < attackEnd)
      env = t / attackEnd;
    else if (t > releaseStart)
      env = (durationMs / 1000.0 - t) / 0.02;

    sample *= env * 0.6;
    qint16 val = static_cast<qint16>(sample * 32767);
    qToLittleEndian<qint16>(val, reinterpret_cast<uchar *>(pcmData.data() + i * 2));
  }

  // Build WAV file in memory
  QByteArray wav;
  QDataStream stream(&wav, QIODevice::WriteOnly);
  stream.setByteOrder(QDataStream::LittleEndian);

  // RIFF header
  stream << QByteArray("RIFF");
  stream << quint32(36 + pcmData.size());
  stream << QByteArray("WAVE");

  // fmt chunk
  stream << QByteArray("fmt ");
  stream << quint32(16);
  stream << quint16(1);        // PCM
  stream << quint16(1);        // mono
  stream << quint32(sampleRate);
  stream << quint32(sampleRate * 2);
  stream << quint16(2);
  stream << quint16(16);

  // data chunk
  stream << QByteArray("data");
  stream << quint32(pcmData.size());
  stream.writeRawData(pcmData.constData(), pcmData.size());

  return wav;
}

static QSoundEffect *loadEffect(const QByteArray &wavData) {
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

SoundManager::SoundManager(QObject *parent) : QObject(parent) {
  m_rotate = loadEffect(generateTone({880}, 50));
  m_drop = loadEffect(generateTone({200, 150}, 100));
  m_lineClear = loadEffect(generateTone({523, 659, 784}, 300));
  m_gameOver = loadEffect(generateTone({440, 370, 311, 262}, 800));
}

void SoundManager::playRotate() {
  if (m_rotate && m_rotate->status() != QSoundEffect::Loading)
    m_rotate->play();
}

void SoundManager::playDrop() {
  if (m_drop && m_drop->status() != QSoundEffect::Loading)
    m_drop->play();
}

void SoundManager::playLineClear() {
  if (m_lineClear && m_lineClear->status() != QSoundEffect::Loading)
    m_lineClear->play();
}

void SoundManager::playGameOver() {
  if (m_gameOver && m_gameOver->status() != QSoundEffect::Loading)
    m_gameOver->play();
}

void SoundManager::setMuted(bool muted) {
  float vol = muted ? 0.0f : 1.0f;
  if (m_rotate) m_rotate->setVolume(vol);
  if (m_drop) m_drop->setVolume(vol);
  if (m_lineClear) m_lineClear->setVolume(vol);
  if (m_gameOver) m_gameOver->setVolume(vol);
}
