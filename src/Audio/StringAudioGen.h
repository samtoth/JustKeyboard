//
// Created by samt on 04/04/2020.
//

#ifndef JUSTKEYBOARD_STRINGAUDIOGEN_H
#define JUSTKEYBOARD_STRINGAUDIOGEN_H


#include <QObject>
#include "../../thirdparty/stk/include/SineWave.h"

class StringAudioGen : public QObject {
    Q_OBJECT
public:
    StringAudioGen();

    virtual ~StringAudioGen();

    float tick();

    float getFrequency() const {return frequency;}
    void setFrequency(float frequency) {StringAudioGen::frequency = frequency; sine->setFrequency(frequency);}

private:
    float frequency;
    stk::SineWave* sine;
};


#endif //JUSTKEYBOARD_STRINGAUDIOGEN_H
