#ifndef UTILS_COLORUTILS_H_
#define UTILS_COLORUTILS_H_

#include "../Config.h"
#include <cmath> // exp

static float calculateGradientValue(float c1, float c2, float factor) {
    return (c2 - c1) * factor + c1; // dla c2 < c1 też zadziała
}

static void calculateSmokeColor(float * out, float textureValue) {
    float nonLinearValue = (1 - exp(-4 * textureValue + config::smokeColorThreshold)); // 0.0 - 1.0

    for(int i = 0; i < 3; ++i) { // r, g, b
        out[i] = nonLinearValue < 0
                ? 0 // bo przez przesunięcie zejdzie poniżej 0
                : calculateGradientValue(config::colorSmokeDark[i], config::colorSmokeBright[i], nonLinearValue);
    }
    out[3] = 0.1; // alpha
}

#endif /* UTILS_COLORUTILS_H_ */
