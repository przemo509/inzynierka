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
	static const bool dumpFrames = false;
	static const bool drawDomain = true;

	static const float simulationSpaceSize = 50;

	static const float dt = 0.25;
	static const float viscosity = 0.001;
	static const float diffusionRate = 0.001;

	static const int mainSourceStartFrame = 0;
	static const int mainSourceHeight = 30;
	static const int mainSourceRadius = 20;
	static const int mainSourceCenterX = 0 + mainSourceRadius + 5; // po lewej stronie, trochę dalej od krawędzi;
	static const int mainSourceCenterZ = simulationSpaceSize / 2;
	static const float mainSourceDensity = 0.9;
	static const float mainSourceSpreadFactor = 3.0;
	static const float mainSourcePhase1VY = 1.0;
	static const int mainSourceStartPhase2Frame = 15;
	static const float mainSourcePhase2VY = 10.0;
	static const int mainSourceStartPhase3Frame = 40;
	static const float mainSourcePhase3VY = 1.0;

	static const float gravityFactor = 0;
	static const float windFactor = 0;

	static const int relaxationSteps = 12; // liczba iteracji relaksacji Gaussa-Seidela

}

#endif /* CONFIG_H_ */
