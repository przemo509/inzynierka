/*
 * Scene.cpp
 *
 *  Created on: 24 sty 2014
 *      Author: Przemo
 */

#include "Scene.h"

Scene::Scene() {
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::draw(Camera *camera) {

	skybox.draw();
    visualization.drawDensities(camera, &simulation);
}
