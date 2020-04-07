//
// Created by Sam on 06/04/2020.
//

#ifndef JUSTKEYBOARD_RATIOS_H
#define JUSTKEYBOARD_RATIOS_H

#include <QString>

namespace RATIOS {
    inline int numerators[13] = {5, 6, 4, 3, 4, 2, 1, 3, 5, 5, 7, 7, 7};
    inline int denominators[13] = {7, 7, 7, 5, 5, 3, 1, 2, 4, 3, 4, 6, 5};
    inline QString labels[13] = {"5/7", "6/7", "4/7", "3/5", "4/5", "2/3", "1", "3/2", "5/4", "5/3", "7/4", "7/6", "7/5"};

    inline float ratios(int i) {
        return numerators[i] / (float) denominators[i];
    }
}
#endif //JUSTKEYBOARD_RATIOS_H

