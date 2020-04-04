//
// Created by samt on 04/04/2020.
//

#include "StringAudioGen.h"

StringAudioGen::StringAudioGen() {
    sine = new stk::SineWave();
    sine->setFrequency(0);
}

StringAudioGen::~StringAudioGen() {
    delete sine;
}

float StringAudioGen::tick() {
    return (float)sine->tick();
}

