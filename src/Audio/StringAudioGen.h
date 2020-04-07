//
// Created by samt on 04/04/2020.
//

#ifndef JUSTKEYBOARD_STRINGAUDIOGEN_H
#define JUSTKEYBOARD_STRINGAUDIOGEN_H


#include <QObject>
#include <stk/include/Bowed.h>

class StringAudioGen : public QObject {
    Q_OBJECT
public:
    StringAudioGen(float fundF, int sampleR);

    virtual ~StringAudioGen();

    float tick();

    float getFrequency() const {return frequency;}
    void setFrequency(float freq) {
        if(freq!=frequency) {
            if(freq == 0){
                string->noteOff(0.99);
            }else{
                string->noteOn(freq, 1./8);
            }
            frequency = freq;
        }
    }

private:
    float fundamentalF;
    float frequency;
    stk::Bowed* string;
};


#endif //JUSTKEYBOARD_STRINGAUDIOGEN_H
