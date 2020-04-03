//
// Created by samt on 02/04/2020.
//

#include "QRTAudioIO.h"

QRTAudioIO::QRTAudioIO(QObject *parent):
        QIODevice(parent)
{
    sine = new stk::SineWave;

    sine->setFrequency(440.0);
}

bool QRTAudioIO::open(QIODevice::OpenMode mode) {
    setOpenMode(mode);
    return true;
}


void QRTAudioIO::close() {
    setOpenMode(NotOpen);
}

bool QRTAudioIO::isSequential() const {return true;}

qint64 QRTAudioIO::readData(char *data, qint64 maxSize) {
    float *samples = (float *) data;
    int nSamples =((int)maxSize)/(SAMPLE_SIZE);
    for (int i = 0; i < nSamples;i++) {
        *samples++ = (float) sine->tick();
    }

    return maxSize;
}

qint64 QRTAudioIO::writeData(const char *data, qint64 maxSize) {
    return -1;
}

QRTAudioIO::~QRTAudioIO() {
    delete sine;
}
