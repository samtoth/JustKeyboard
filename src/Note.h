//
// Created by Sam on 08/03/2020.
//

#ifndef TRADE_NOTE_H
#define TRADE_NOTE_H

#include <string>
#include <sstream>
#include <cmath>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

inline const char Notes[12][3] = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B" };

inline std::string getNoteName(float freq, int *midiCentDiff) {
    int a = 440; //frequency of A (common value is 440Hz)
    float midic = (12 * std::log2(freq /(float)a)) + 69; //A4 is midi 69
    *midiCentDiff = roundf((-roundf(midic)+midic)*100);
    int midi = round(midic);
    int octave = (midi / 12) - 1;
    return std::string(Notes[midi%12]) + SSTR(octave);
}


#endif //TRADE_NOTE_H
