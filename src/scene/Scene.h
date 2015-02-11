/*
 * Scene.h
 *
 *  Created on: 24 sty 2014
 *      Author: Przemo
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "../simulation/ExplosionSimulation.h"
#include "../simulation/ExplosionVisualization.h"
#include "Camera.h"
#include "Skybox.h"

class Scene {
public:
	Scene();
	virtual ~Scene();
	void draw(Camera *camera);
	ExplosionSimulation simulation;
	ExplosionVisualization visualization;

private:
	Skybox skybox;
};

#endif /* SCENE_H_ */
