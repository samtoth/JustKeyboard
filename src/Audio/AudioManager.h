//
// Created by samt on 03/04/2020.
//

#ifndef JUSTKEYBOARD_AUDIOMANAGER_H
#define JUSTKEYBOARD_AUDIOMANAGER_H


#include "QRTAudioIO.h"
#include <QAudioOutput>
#include "StringAudioGen.h"

class AudioManager : public QObject{
    Q_OBJECT
public:
    AudioManager();
    virtual ~AudioManager();

    void setStringPitch(int string, float freq);

    void start();
    void stop();
private:
    bool configureAudioOutput();

    StringAudioGen* strings[13];

    QRTAudioIO *audioIO;
    QAudioOutput* audioOutput; // class member.
public slots:
    float tick();
};


#endif //JUSTKEYBOARD_AUDIOMANAGER_H
