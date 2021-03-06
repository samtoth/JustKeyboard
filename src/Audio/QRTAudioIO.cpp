//
// Created by samt on 02/04/2020.
//

#include "QRTAudioIO.h"

QRTAudioIO::QRTAudioIO(QObject *parent):
        QIODevice(parent)
{}

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
        //*samples++ = (float) (frequency==0?0:sine->tick());
        *samples++ = tick();
    }

    return maxSize;
}

qint64 QRTAudioIO::writeData(const char *data, qint64 maxSize) {
    return 0;
}

QRTAudioIO::~QRTAudioIO() {}

bool QRTAudioIO::seek(qint64 pos) {
    //qWarning("QIODevice::seek: Cannot call seek on a sequential device");
    return false;
}

