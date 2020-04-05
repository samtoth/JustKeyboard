//
// Created by samt on 03/04/2020.
//

#include "AudioManager.h"

AudioManager::AudioManager(){
}

AudioManager::~AudioManager() {
    audioOutput->stop();

    for(int i = 0; i<13; i++){
        delete strings[i];
    }

    delete audioOutput;
    delete audioIO;
    qDebug() << "Audio manager safely cleaned up";
}


bool AudioManager::configureAudioOutput() {
    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(SAMPLE_RATE);
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

    audioOutput = new QAudioOutput(format, NULL);
    audioOutput->setBufferSize(SAMPLE_SIZE * SAMPLE_RATE * 0.03f);
    return true;
}

void AudioManager::start() {
    if (configureAudioOutput()) {
        audioIO = new QRTAudioIO;
        audioIO->open(QIODevice::ReadOnly);
        for(int i = 0; i < 13; i++){
            strings[i] = new StringAudioGen();
        }
        connect(audioIO, &QRTAudioIO::tick, this, &AudioManager::tick);
        audioOutput->start(audioIO);
        qDebug() << "Audio manager started";
    }
}

void AudioManager::stop() {
    audioOutput->stop();
}

void AudioManager::setStringPitch(int string, float freq) {
    if(strings[string]->getFrequency()!=freq) {
        strings[string]->setFrequency(freq);
    }
}

float AudioManager::tick() {
    float result = 0;
    for(int i =0; i<13; i++){
        result += strings[i]->tick();
    }
    return result/13.f;
}


