//
// Created by samt on 04/04/2020.
//

#include "StringAudioGen.h"

StringAudioGen::StringAudioGen(float fundF, int sampleR) {
    fundamentalF = fundF;
    string = new stk::Bowed(fundamentalF);
    string->setSampleRate(sampleR);
    string->setVibrato(0.005);
}

StringAudioGen::~StringAudioGen() {
    delete string;
}

float StringAudioGen::tick() {
    return (float)string->tick();
}

