//
// Created by samt on 02/04/2020.
//

#ifndef JUSTKEYBOARD_QRTAUDIOIO_H
#define JUSTKEYBOARD_QRTAUDIOIO_H

#include <QAudio>
#include <QIODevice>


#define SAMPLE_SIZE sizeof(float)


class QRTAudioIO : public QIODevice{
Q_OBJECT
public:
    explicit QRTAudioIO(QObject* parent = 0);
    virtual ~QRTAudioIO();

    bool open(OpenMode mode) override;
    void close() override;
    bool isSequential() const override;
protected:
    qint64 readData(char* data, qint64 maxSize) override;
    qint64 writeData(const char* data, qint64 maxSize) override;
private:
    Q_DISABLE_COPY(QRTAudioIO)
signals:
    float tick();
};


#endif //JUSTKEYBOARD_QRTAUDIOIO_H
