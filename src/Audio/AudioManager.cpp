//
// Created by samt on 03/04/2020.
//

#include "AudioManager.h"

AudioManager::AudioManager(){
}

AudioManager::~AudioManager() {
    audio->stop();
    delete audio;
    delete audioIO;
    qDebug() << "Audio manager safely cleaned up";
}


bool AudioManager::configureAudioOutput() {
    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(44100.0);
    format.setChannelCount(1);
    format.setSampleSize(SAMPLE_SIZE*8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::Float);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return false;
    }

    //qDebug() << "Audio format: " << format.bytesPerFrame() << " bytes per frame";

    audio = new QAudioOutput(format, NULL);
    return true;
}

void AudioManager::start() {
    if (configureAudioOutput()) {
    audioIO = new QRTAudioIO;
    audioIO->open(QIODevice::ReadOnly);
    audio->start(audioIO);
    qDebug() << "Audio manager started";
    }
}

void AudioManager::stop() {
    audio->stop();
}
