//
// Created by samt on 02/04/2020.
//

#ifndef JUSTKEYBOARD_QRTAUDIOIO_H
#define JUSTKEYBOARD_QRTAUDIOIO_H

#include <QAudio>
#include <QIODevice>
#include "../../thirdparty/stk/include/SineWave.h"


#define SAMPLE_SIZE sizeof(float)


class QRTAudioIO : public QIODevice{
Q_OBJECT
public:
    explicit QRTAudioIO(QObject* parent = 0);
    virtual ~QRTAudioIO();

    bool open(OpenMode mode);
    void close();
    bool isSequential() const;

    void setFreq(float freq);
protected:
    qint64 readData(char* data, qint64 maxSize);
    qint64 writeData(const char* data, qint64 maxSize);
private:
    stk::SineWave* sine;
    float frequency;
    Q_DISABLE_COPY(QRTAudioIO)
};


#endif //JUSTKEYBOARD_QRTAUDIOIO_H
