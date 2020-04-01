//
// Created by samt on 01/04/2020.
//

#ifndef JUSTKEYBOARD_PLAYBACK_H
#define JUSTKEYBOARD_PLAYBACK_H

#endif //JUSTKEYBOARD_PLAYBACK_H

#include "stk/SineWave.h"
#include "stk/RtWvOut.h"
#include <cstdlib>
using namespace stk;
class PlaybackEngine {
public:
    void play();
    void stop();
private:
    RtAudio dac;
    void cleanup();
};

