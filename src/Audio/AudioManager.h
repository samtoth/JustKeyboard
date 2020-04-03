//
// Created by samt on 03/04/2020.
//

#ifndef JUSTKEYBOARD_AUDIOMANAGER_H
#define JUSTKEYBOARD_AUDIOMANAGER_H


#include "QRTAudioIO.h"
#include <QDebug>
#include <QAudioOutput>
#include <QThread>

class AudioManager : public QObject{
    Q_OBJECT
public:
    AudioManager();
    virtual ~AudioManager();

    void setPitch(float freq);

    void start();
    void stop();
private:
    bool configureAudioOutput();

    QRTAudioIO *audioIO;
    QAudioOutput* audio; // class member.
};


#endif //JUSTKEYBOARD_AUDIOMANAGER_H
