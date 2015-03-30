/*
 * Config.h
 *
 *  Created on: 7 lut 2015
 *      Author: Przemo
 */

#ifndef CONFIG_H_
#define CONFIG_H_

namespace config {
    static const bool autoPlay = true;
    static const bool dumpFrames = true;
    static const bool drawDomain = false;
    static const bool drawVortices = false;
    static const int maxFrames = 200;

    static const bool simulateTurbulences = true;
    static const int vorticesCount = 200;
    static const float vortexStrenght = 0.01;
    static const int vortexMoving = 20;
    static const int vortexRadiusMin = 2;
    static const int vortexRadiusMax = 3;

    static const int simulationSpaceSize = 50;

    static const float dt = 0.25;
    static const float viscosity = 0.0001;
    static const float diffusionRate = 0.0001;

    static const int mainSourceHeight = 3;
    static const int mainSourceRadius = 10;
    static const int mainSourceCenterX = 0 + mainSourceRadius + 5; // po lewej stronie, trochę dalej od krawędzi;
    static const int mainSourceCenterZ = simulationSpaceSize / 2;
    static const float mainSourceDensity = 0.1;
    static const float mainSourceSpreadFactor = 0.2;
    static const float vySlow = 0.02;
    static const float vyMedium = 0.5;
    static const float vyFast = 0.6;
    static const float mainSourceVY = vySlow;
    static const float explosionSource[][2] = {
                                             {0, 0.0},
                                             {5, vySlow},
                                             {30, vyMedium},
                                             {60, vyFast},
                                             {85, vySlow},
                                             {110, vyMedium},
                                             {160, vyFast},
                                             {maxFrames, 0.0}
    };
    static const int explosionSourcePhases = sizeof(explosionSource)/sizeof(config::explosionSource[0]);

    static const float thermalBuoyancyFactor = 0.8;

    static const float gravityFactor = 0.003;
    static const float windFactor = 0.1;

    static const int relaxationSteps = 12; // liczba iteracji relaksacji Gaussa-Seidela

    // wizualizacja
    static const float distanceFactor = 0.01;
    static const int textureResolution = 256;

}

#endif /* CONFIG_H_ */
