#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include <cstdlib>

static int rand(int from, int to) {
    return rand() % (to - from + 1) + from;
}

static int randAround(int middle, int spread) {
    return middle + rand(-spread, spread);
}

static float randFloat(float from, float to) {
    return 1.0 * rand() / RAND_MAX * (to - from) + from;
}

static float randAroundFloat(float middle, float spread) {
    return middle + randFloat(-spread, spread);
}

#endif /* MATHUTILS_H_ */
