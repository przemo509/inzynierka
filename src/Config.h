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

	static const float simulationSpaceSize = 50;

	static const float dt = 0.25;
	static const float viscosity = 0.001;
	static const float diffusionRate = 0.001;

	static const int mainSourceHeight = 3;
	static const int mainSourceRadius = 5;
	static const int mainSourceCenterX = 0 + mainSourceRadius + 5; // po lewej stronie, trochę dalej od krawędzi;
	static const int mainSourceCenterZ = simulationSpaceSize / 2;
	static const float mainSourceDensity = 0.4;
	static const float mainSourceSpreadFactor = 0.01;
	static const int mainSourceStartFrame = 5;
	static const int mainSourceStartPhase2Frame = 15;
	static const int mainSourceStartPhase3Frame = 40;
	static const float mainSourcePhase1VY = 2.0;
	static const float mainSourcePhase2VY = 4.0;
	static const float mainSourcePhase3VY = 4.0;

	static const float thermalBuoyancyFactor = 0.1;

	static const float gravityFactor = 0.001;
	static const float windFactor = 0.2;

	static const int relaxationSteps = 12; // liczba iteracji relaksacji Gaussa-Seidela

	// wizualizacja
    static const float distanceFactor = 0.01;
    static const int textureResolution = 256;

}

#endif /* CONFIG_H_ */
